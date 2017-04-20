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

#if defined(MSYS)
#define __USE_LINUX_IOCTL_DEFS
#endif
#include <sys/ioctl.h>
#if defined(MSYS)
// There's no spidev.h on MSYS, so we need to provide our own,
// and only *after* including ioctl.h as that one contains prerequisites.
#include "linux/spi_kernel_headers.h"
#else
#include <linux/spi/spidev.h>
#endif

#include "common.h"
#include "fogdevices/fogdevices_board_spi.h"

mraa_result_t
mraa_fogdevices_spi_init_raw_replace(mraa_spi_context dev, unsigned int bus, unsigned int cs)
{
    return MRAA_ERROR_FEATURE_NOT_IMPLEMENTED;
}

mraa_result_t
mraa_fogdevices_spi_stop_replace(mraa_spi_context dev)
{
    return MRAA_ERROR_FEATURE_NOT_IMPLEMENTED;
}

mraa_result_t
mraa_fogdevices_spi_bit_per_word_replace(mraa_spi_context dev, unsigned int bits)
{
    return MRAA_ERROR_FEATURE_NOT_IMPLEMENTED;
}

mraa_result_t
mraa_fogdevices_spi_lsbmode_replace(mraa_spi_context dev, mraa_boolean_t lsb)
{
    return MRAA_ERROR_FEATURE_NOT_IMPLEMENTED;
}

mraa_result_t
mraa_fogdevices_spi_mode_replace(mraa_spi_context dev, mraa_spi_mode_t mode)
{
    return MRAA_ERROR_FEATURE_NOT_IMPLEMENTED;
}

mraa_result_t
mraa_fogdevices_spi_frequency_replace(mraa_spi_context dev, int hz)
{
    return MRAA_ERROR_FEATURE_NOT_IMPLEMENTED;
}

int
mraa_fogdevices_spi_write_replace(mraa_spi_context dev, uint8_t data)
{
    return -1;
}

int
mraa_fogdevices_spi_write_word_replace(mraa_spi_context dev, uint16_t data)
{
    return -1;
}

mraa_result_t
mraa_fogdevices_spi_transfer_buf_replace(mraa_spi_context dev, uint8_t* data, uint8_t* rxbuf, int length)
{
    return MRAA_ERROR_FEATURE_NOT_IMPLEMENTED;
}

mraa_result_t
mraa_fogdevices_spi_transfer_buf_word_replace(mraa_spi_context dev, uint16_t* data, uint16_t* rxbuf, int length)
{
    return MRAA_ERROR_FEATURE_NOT_IMPLEMENTED;
}
