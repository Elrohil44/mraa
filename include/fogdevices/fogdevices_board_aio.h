#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "mraa_internal.h"

mraa_result_t
mraa_fogdevices_aio_init_internal_replace(mraa_aio_context dev, int pin);

mraa_result_t
mraa_fogdevices_aio_close_replace(mraa_aio_context dev);

int
mraa_fogdevices_aio_read_replace(mraa_aio_context dev);

#ifdef __cplusplus
}
#endif
