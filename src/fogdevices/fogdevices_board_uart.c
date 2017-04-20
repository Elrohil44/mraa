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

#include "common.h"
#include "fogdevices/fogdevices_board_uart.h"

mraa_result_t
mraa_fogdevices_uart_set_baudrate_replace(mraa_uart_context dev, unsigned int baud)
{
    return MRAA_ERROR_FEATURE_NOT_IMPLEMENTED;
}

mraa_result_t
mraa_fogdevices_uart_init_raw_replace(mraa_uart_context dev, const char* path)
{
    return MRAA_ERROR_FEATURE_NOT_IMPLEMENTED;
}

mraa_result_t
mraa_fogdevices_uart_flush_replace(mraa_uart_context dev)
{
    return MRAA_ERROR_FEATURE_NOT_IMPLEMENTED;
}

mraa_result_t
mraa_fogdevices_uart_set_flowcontrol_replace(mraa_uart_context dev, mraa_boolean_t xonxoff, mraa_boolean_t rtscts)
{
    return MRAA_ERROR_FEATURE_NOT_IMPLEMENTED;
}

mraa_result_t
mraa_fogdevices_uart_set_mode_replace(mraa_uart_context dev, int bytesize, mraa_uart_parity_t parity, int stopbits)
{
    return MRAA_ERROR_FEATURE_NOT_IMPLEMENTED;
}

mraa_result_t
mraa_fogdevices_uart_set_non_blocking_replace(mraa_uart_context dev, mraa_boolean_t nonblock)
{
    return MRAA_ERROR_FEATURE_NOT_IMPLEMENTED;
}

mraa_result_t
mraa_fogdevices_uart_set_timeout_replace(mraa_uart_context dev, int read, int write, int interchar)
{
    return MRAA_ERROR_FEATURE_NOT_IMPLEMENTED;
}

mraa_boolean_t
mraa_fogdevices_uart_data_available_replace(mraa_uart_context dev, unsigned int millis)
{
    return 0;
}

int
mraa_fogdevices_uart_write_replace(mraa_uart_context dev, const char* buf, size_t len)
{
    return 0;
}

int
mraa_fogdevices_uart_read_replace(mraa_uart_context dev, char* buf, size_t len)
{
    return 0;
}
