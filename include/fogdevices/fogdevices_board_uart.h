#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "mraa_internal.h"

mraa_result_t
mraa_fogdevices_uart_set_baudrate_replace(mraa_uart_context dev, unsigned int baud);

mraa_result_t
mraa_fogdevices_uart_init_raw_replace(mraa_uart_context dev, const char* path);

mraa_result_t
mraa_fogdevices_uart_flush_replace(mraa_uart_context dev);

mraa_result_t
mraa_fogdevices_uart_set_flowcontrol_replace(mraa_uart_context dev, mraa_boolean_t xonxoff, mraa_boolean_t rtscts);

mraa_result_t
mraa_fogdevices_uart_set_mode_replace(mraa_uart_context dev, int bytesize, mraa_uart_parity_t parity, int stopbits);

mraa_result_t
mraa_fogdevices_uart_set_non_blocking_replace(mraa_uart_context dev, mraa_boolean_t nonblock);

mraa_result_t
mraa_fogdevices_uart_set_timeout_replace(mraa_uart_context dev, int read, int write, int interchar);

mraa_boolean_t
mraa_fogdevices_uart_data_available_replace(mraa_uart_context dev, unsigned int millis);

int
mraa_fogdevices_uart_write_replace(mraa_uart_context dev, const char* buf, size_t len);

int
mraa_fogdevices_uart_read_replace(mraa_uart_context dev, char* buf, size_t len);

#ifdef __cplusplus
}
#endif
