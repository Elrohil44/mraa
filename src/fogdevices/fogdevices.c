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

#include "mraa_internal.h"

#include "fogdevices/fogdevices_board.h"

mraa_platform_t
mraa_fogdevices_platform(char* mqtt_id, char* mqtt_broker)
{
    mraa_platform_t platform_type = MRAA_FOGDEVICES_PLATFORM;
    plat = mraa_fogdevices_board(mqtt_id, mqtt_broker);

    if (plat == NULL) {
        syslog(LOG_ERR, "Was not able to initialize fogdevices platform");
        return MRAA_ERROR_PLATFORM_NOT_INITIALISED;
    }

    return platform_type;
}
