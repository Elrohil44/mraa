#ifndef _FOGDEVICES_H_
#define	_FOGDEVICES_H_

#include "mqtt/MQTTClient.h"

#define ADDRESS     "tcp://iot.eclipse.org:1883"
#define CLIENTID    "ExampleClientPub"

MQTTClient client;
char* client_id;

int fogdev_gpio[4];
int fogdev_aio[4];


#endif /* !_FOGDEVICES_H_ */
