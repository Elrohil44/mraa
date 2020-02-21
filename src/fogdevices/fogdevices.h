#ifndef _FOGDEVICES_H_
#define	_FOGDEVICES_H_

#include "mqtt/MQTTClient.h"
#include <inttypes.h>

#define ADDRESS     "tcp://iot.eclipse.org:1883"
#define CLIENTID    "ExampleClientPub"

#define ADC 0
#define I2C 1
#define GPIO 2

MQTTClient client;
char* client_id;

int fogdev_gpio[4];
int fogdev_aio[4];
uint8_t fogdev_bme280_i2c[256];


#endif /* !_FOGDEVICES_H_ */
