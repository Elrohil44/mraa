/*
 * Author: Tomasz Szydlo <tomasz.szydlo@agh.edu.pl>
 * based on mock platform by Alex Tereschenko <alext.mkrs@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "fogdevices.h"

#include "common.h"
#include "fogdevices/fogdevices_board.h"
#include "fogdevices/fogdevices_board_gpio.h"
#include "fogdevices/fogdevices_board_aio.h"
#include "fogdevices/fogdevices_board_i2c.h"
#include "fogdevices/fogdevices_board_spi.h"
#include "fogdevices/fogdevices_board_uart.h"

#define PLATFORM_NAME "MRAA fogdevices platform"
#define UART_DEV_PATH "dummy"

volatile MQTTClient_deliveryToken deliveredtoken;

void delivered(void *context, MQTTClient_deliveryToken dt)
{
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredtoken = dt;
}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    printf("Message arrived\n");
    printf("     topic: %s\n", topicName);
    printf("   message: ");

    float val = 0;
    val = strtof(message->payload, NULL);
    float i2c_value = 0;
    int32_t i2c_value_int = 0;
    uint32_t i2c_value_uint = 0;

    int pin;
    int type;
    pin = topicName[strlen(topicName)-1]-'0';

    if (topicName[strlen(topicName)-5]=='A')
    {
        type = ADC;
    }
    else if (topicName[strlen(topicName)-5]=='I')
    {
        type = I2C;
        i2c_value = strtof(&message->payload[8], NULL);
    }
    else
    {
        type = GPIO;
    }

    printf("Type=%d Pin=%d Value=%f\n",type,pin,val);


    switch (type) {
        case ADC:
            fogdev_aio[pin] = (int) val;
            break;
        case GPIO:
            fogdev_gpio[pin] = (int) val;
            break;
        case I2C:
            switch (((char*) message->payload)[7]) {
                case HUMIDITY:
                    i2c_value_int = i2c_value * 1024;
                    i2c_value_uint = i2c_value_int;
                    fogdev_bme280_i2c[0xfd] = i2c_value_uint >> 8;
                    fogdev_bme280_i2c[0xfe] = i2c_value_uint;
                    break;
                case TEMPERATURE:
                    i2c_value_int = (i2c_value < 0 ? -i2c_value * 100 : i2c_value * 100);
                    i2c_value_uint = i2c_value_int;
                    fogdev_bme280_i2c[0xfa] = i2c_value > 0 ? (i2c_value_uint >> 12) & 0x7f : (i2c_value_uint >> 12) | 0x80;
                    fogdev_bme280_i2c[0xfb] = i2c_value_uint >> 4;
                    fogdev_bme280_i2c[0xfc] = i2c_value_uint << 4;
                    break;
                case PRESSURE:
                    i2c_value_int = i2c_value * 256;
                    i2c_value_uint = i2c_value_int;
                    fogdev_bme280_i2c[0xf7] = i2c_value_uint >> 12;
                    fogdev_bme280_i2c[0xf8] = i2c_value_uint >> 4;
                    fogdev_bme280_i2c[0xf9] = i2c_value_uint << 4;
                    break;
            }
        default: ;
    }

    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

void connlost(void *context, char *cause)
{
    printf("\nConnection lost\n");
    printf("     cause: %s\n", cause);
}

mraa_board_t*
mraa_fogdevices_board(char* mqtt_id, char* mqtt_broker)
{

    if (mqtt_id == NULL || mqtt_broker == NULL){
        mqtt_id = CLIENTID;
        mqtt_broker = ADDRESS;
    }


    mraa_board_t* b = (mraa_board_t*) calloc(1, sizeof(mraa_board_t));
    if (b == NULL) {
        return NULL;
    }

    //MQTT connection
    
    printf("[MQTT] Initialization");
//    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;

    MQTTClient_create(&client, mqtt_broker, mqtt_id,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered);

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
    }


    //store the cient id for MQTT protocol communication    
    client_id = mqtt_id;


    //char* topic = "fogdevicesplatform/[ID]/slave/";
    char topic[128];
    sprintf(topic, "fogdevicesplatform/%s/slave/#",client_id);

    //subscribe for the messages from master
    MQTTClient_subscribe(client, topic, 0);


    // General board definitions
    b->platform_name = PLATFORM_NAME;
    b->phy_pin_count = MRAA_FOGDEVICES_PINCOUNT;
    b->gpio_count = 4;
    b->aio_count = 4;
    b->adc_raw = 12;
    b->adc_supported = 10;

    b->i2c_bus_count = 1;
    b->i2c_bus[0].bus_id = 0;
    b->i2c_bus[0].sda = 8;
    b->i2c_bus[0].scl = 9;
    b->def_i2c_bus = b->i2c_bus[0].bus_id;

    b->spi_bus_count = 0;
    /*b->spi_bus_count = 1;
    b->def_spi_bus = 0;
    b->spi_bus[0].bus_id = 0;
    b->spi_bus[0].slave_s = 0;
    b->spi_bus[0].cs = 4;
    b->spi_bus[0].mosi = 5;
    b->spi_bus[0].miso = 6;
    b->spi_bus[0].sclk = 7;*/

    b->pwm_default_period = 0;
    b->pwm_max_period = 0;
    b->pwm_min_period = 0;

    b->uart_dev_count = 0;
    /*b->uart_dev_count = 1;
    b->def_uart_dev = 0;
    b->uart_dev[0].rx = 8;
    b->uart_dev[0].tx = 9;
    b->uart_dev[0].device_path = UART_DEV_PATH;*/

    b->pins = (mraa_pininfo_t*) malloc(sizeof(mraa_pininfo_t) * MRAA_FOGDEVICES_PINCOUNT);
    if (b->pins == NULL) {
        goto error;
    }

    b->adv_func = (mraa_adv_func_t*) calloc(1, sizeof(mraa_adv_func_t));
    if (b->adv_func == NULL) {
        free(b->pins);
        goto error;
    }

    // Replace functions
    b->adv_func->gpio_init_internal_replace = &mraa_fogdevices_gpio_init_internal_replace;
    b->adv_func->gpio_close_replace = &mraa_fogdevices_gpio_close_replace;
    b->adv_func->gpio_dir_replace = &mraa_fogdevices_gpio_dir_replace;
    b->adv_func->gpio_read_dir_replace = &mraa_fogdevices_gpio_read_dir_replace;
    b->adv_func->gpio_read_replace = &mraa_fogdevices_gpio_read_replace;
    b->adv_func->gpio_write_replace = &mraa_fogdevices_gpio_write_replace;
    b->adv_func->gpio_edge_mode_replace = &mraa_fogdevices_gpio_edge_mode_replace;
    b->adv_func->gpio_isr_replace = &mraa_fogdevices_gpio_isr_replace;
    b->adv_func->gpio_isr_exit_replace = &mraa_fogdevices_gpio_isr_exit_replace;
    b->adv_func->gpio_mode_replace = &mraa_fogdevices_gpio_mode_replace;
    b->adv_func->aio_init_internal_replace = &mraa_fogdevices_aio_init_internal_replace;
    b->adv_func->aio_close_replace = &mraa_fogdevices_aio_close_replace;
    b->adv_func->aio_read_replace = &mraa_fogdevices_aio_read_replace;
    b->adv_func->i2c_init_bus_replace = &mraa_fogdevices_i2c_init_bus_replace;
    b->adv_func->i2c_stop_replace = &mraa_fogdevices_i2c_stop_replace;
    b->adv_func->i2c_set_frequency_replace = &mraa_fogdevices_i2c_set_frequency_replace;
    b->adv_func->i2c_address_replace = &mraa_fogdevices_i2c_address_replace;
    b->adv_func->i2c_read_replace = &mraa_fogdevices_i2c_read_replace;
    b->adv_func->i2c_read_byte_replace = &mraa_fogdevices_i2c_read_byte_replace;
    b->adv_func->i2c_read_byte_data_replace = &mraa_fogdevices_i2c_read_byte_data_replace;
    b->adv_func->i2c_read_bytes_data_replace = &mraa_fogdevices_i2c_read_bytes_data_replace;
    b->adv_func->i2c_read_word_data_replace = &mraa_fogdevices_i2c_read_word_data_replace;
    b->adv_func->i2c_write_replace = &mraa_fogdevices_i2c_write_replace;
    b->adv_func->i2c_write_byte_replace = &mraa_fogdevices_i2c_write_byte_replace;
    b->adv_func->i2c_write_byte_data_replace = &mraa_fogdevices_i2c_write_byte_data_replace;
    b->adv_func->i2c_write_word_data_replace = &mraa_fogdevices_i2c_write_word_data_replace;
    b->adv_func->spi_init_raw_replace = &mraa_fogdevices_spi_init_raw_replace;
    b->adv_func->spi_stop_replace = &mraa_fogdevices_spi_stop_replace;
    b->adv_func->spi_bit_per_word_replace = &mraa_fogdevices_spi_bit_per_word_replace;
    b->adv_func->spi_lsbmode_replace = &mraa_fogdevices_spi_lsbmode_replace;
    b->adv_func->spi_mode_replace = &mraa_fogdevices_spi_mode_replace;
    b->adv_func->spi_frequency_replace = &mraa_fogdevices_spi_frequency_replace;
    b->adv_func->spi_write_replace = &mraa_fogdevices_spi_write_replace;
    b->adv_func->spi_write_word_replace = &mraa_fogdevices_spi_write_word_replace;
    b->adv_func->spi_transfer_buf_replace = &mraa_fogdevices_spi_transfer_buf_replace;
    b->adv_func->spi_transfer_buf_word_replace = &mraa_fogdevices_spi_transfer_buf_word_replace;
    b->adv_func->uart_init_raw_replace = &mraa_fogdevices_uart_init_raw_replace;
    b->adv_func->uart_set_baudrate_replace = &mraa_fogdevices_uart_set_baudrate_replace;
    b->adv_func->uart_flush_replace = &mraa_fogdevices_uart_flush_replace;
    b->adv_func->uart_set_flowcontrol_replace = &mraa_fogdevices_uart_set_flowcontrol_replace;
    b->adv_func->uart_set_mode_replace = &mraa_fogdevices_uart_set_mode_replace;
    b->adv_func->uart_set_non_blocking_replace = &mraa_fogdevices_uart_set_non_blocking_replace;
    b->adv_func->uart_set_timeout_replace = &mraa_fogdevices_uart_set_timeout_replace;
    b->adv_func->uart_data_available_replace = &mraa_fogdevices_uart_data_available_replace;
    b->adv_func->uart_write_replace = &mraa_fogdevices_uart_write_replace;
    b->adv_func->uart_read_replace = &mraa_fogdevices_uart_read_replace;

    // Pin definitions
    int pos = 0;

    strncpy(b->pins[pos].name, "GPIO0", 8);
    b->pins[pos].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 0, 0, 0 };
    b->pins[pos].gpio.pinmap = 0;
    b->pins[pos].gpio.mux_total = 0;
    pos++;

    strncpy(b->pins[pos].name, "GPIO1", 8);
    b->pins[pos].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 0, 0, 0 };
    b->pins[pos].gpio.pinmap = 1;
    b->pins[pos].gpio.mux_total = 0;
    pos++;

    strncpy(b->pins[pos].name, "GPIO2", 8);
    b->pins[pos].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 0, 0, 0 };
    b->pins[pos].gpio.pinmap = 2;
    b->pins[pos].gpio.mux_total = 0;
    pos++;

    strncpy(b->pins[pos].name, "GPIO3", 8);
    b->pins[pos].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 0, 0, 0 };
    b->pins[pos].gpio.pinmap = 3;
    b->pins[pos].gpio.mux_total = 0;
    pos++;

    strncpy(b->pins[pos].name, "ADC0", 8);
    b->pins[pos].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 0, 0, 1, 0 };
    b->pins[pos].aio.pinmap = 4;
    b->pins[pos].aio.mux_total = 0;
    pos++;

    strncpy(b->pins[pos].name, "ADC1", 8);
    b->pins[pos].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 0, 0, 1, 0 };
    b->pins[pos].aio.pinmap = 5;
    b->pins[pos].aio.mux_total = 0;
    pos++;

    strncpy(b->pins[pos].name, "ADC2", 8);
    b->pins[pos].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 0, 0, 1, 0 };
    b->pins[pos].aio.pinmap = 6;
    b->pins[pos].aio.mux_total = 0;
    pos++;

    strncpy(b->pins[pos].name, "ADC3", 8);
    b->pins[pos].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 0, 0, 1, 0 };
    b->pins[pos].aio.pinmap = 7;
    b->pins[pos].aio.mux_total = 0;
    pos++;

    strncpy(b->pins[pos].name, "I2C0SDA", 8);
    b->pins[pos].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 0, 1, 0, 0 };
    b->pins[pos].i2c.mux_total = 0;
    b->pins[pos].i2c.pinmap = 0;
    pos++;

    strncpy(b->pins[pos].name, "I2C0SCL", 8);
    b->pins[pos].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 0, 1, 0, 0 };
    b->pins[pos].i2c.mux_total = 0;
    b->pins[pos].i2c.pinmap = 0;
    pos++;
/*
    strncpy(b->pins[pos].name, "SPI0CS", 8);
    b->pins[pos].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 1, 0, 0, 0 };
    b->pins[pos].spi.mux_total = 0;
    b->pins[pos].spi.pinmap = 0;
    pos++;

    strncpy(b->pins[pos].name, "SPI0MOSI", 8);
    b->pins[pos].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 1, 0, 0, 0 };
    b->pins[pos].spi.mux_total = 0;
    b->pins[pos].spi.pinmap = 0;
    pos++;

    strncpy(b->pins[pos].name, "SPI0MISO", 8);
    b->pins[pos].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 1, 0, 0, 0 };
    b->pins[pos].spi.mux_total = 0;
    b->pins[pos].spi.pinmap = 0;
    pos++;

    strncpy(b->pins[pos].name, "SPI0SCLK", 8);
    b->pins[pos].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 1, 0, 0, 0 };
    b->pins[pos].spi.mux_total = 0;
    b->pins[pos].spi.pinmap = 0;
    pos++;

    strncpy(b->pins[pos].name, "UART0RX", 8);
    b->pins[pos].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 0, 0, 0, 1 };
    b->pins[pos].uart.pinmap = 0;
    b->pins[pos].uart.parent_id = 0;
    b->pins[pos].uart.mux_total = 0;
    pos++;

    strncpy(b->pins[pos].name, "UART0TX", 8);
    b->pins[pos].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 0, 0, 0, 1 };
    b->pins[pos].uart.pinmap = 0;
    b->pins[pos].uart.parent_id = 0;
    b->pins[pos].uart.mux_total = 0;
    pos++;
*/

    return b;

error:
    syslog(LOG_CRIT, "MRAA fogdevices: Platform failed to initialise");
    free(b);
    return NULL;
}
