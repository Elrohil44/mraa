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
#include "fogdevices/fogdevices_board_i2c.h"

mraa_result_t
mraa_fogdevices_i2c_init_bus_replace(mraa_i2c_context dev)
{
    return MRAA_ERROR_FEATURE_NOT_IMPLEMENTED;
}

mraa_result_t
mraa_fogdevices_i2c_stop_replace(mraa_i2c_context dev)
{
    return MRAA_ERROR_FEATURE_NOT_IMPLEMENTED;
}


mraa_result_t
mraa_fogdevices_i2c_set_frequency_replace(mraa_i2c_context dev, mraa_i2c_mode_t mode)
{
    return MRAA_ERROR_FEATURE_NOT_IMPLEMENTED;
}

mraa_result_t
mraa_fogdevices_i2c_address_replace(mraa_i2c_context dev, uint8_t addr)
{
    return MRAA_ERROR_FEATURE_NOT_IMPLEMENTED;
}

int
mraa_fogdevices_i2c_read_replace(mraa_i2c_context dev, uint8_t* data, int length)
{
    return -1;
}

int
mraa_fogdevices_i2c_read_byte_replace(mraa_i2c_context dev)
{
    return -1;
}

int
mraa_fogdevices_i2c_read_byte_data_replace(mraa_i2c_context dev, uint8_t command)
{
    return -1;
}

int
mraa_fogdevices_i2c_read_bytes_data_replace(mraa_i2c_context dev, uint8_t command, uint8_t* data, int length)
{
    return -1;
}

int
mraa_fogdevices_i2c_read_word_data_replace(mraa_i2c_context dev, uint8_t command)
{
    return -1;
}

mraa_result_t
mraa_fogdevices_i2c_write_replace(mraa_i2c_context dev, const uint8_t* data, int length)
{
    return MRAA_ERROR_FEATURE_NOT_IMPLEMENTED;
}

mraa_result_t
mraa_fogdevices_i2c_write_byte_replace(mraa_i2c_context dev, const uint8_t data)
{
    return MRAA_ERROR_FEATURE_NOT_IMPLEMENTED;
}

mraa_result_t
mraa_fogdevices_i2c_write_byte_data_replace(mraa_i2c_context dev, const uint8_t data, const uint8_t command)
{
    return MRAA_ERROR_FEATURE_NOT_IMPLEMENTED;
}

mraa_result_t
mraa_fogdevices_i2c_write_word_data_replace(mraa_i2c_context dev, const uint16_t data, const uint8_t command)
{
    return MRAA_ERROR_FEATURE_NOT_IMPLEMENTED;
}
