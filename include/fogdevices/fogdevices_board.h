#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "mraa_internal.h"

#define MRAA_FOGDEVICES_PINCOUNT 10

mraa_board_t*
mraa_fogdevices_board(char*, char*);


#ifdef __cplusplus
}
#endif
