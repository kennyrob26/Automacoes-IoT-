#ifndef _STATUS_BATERIA_H_
#define _STATUS_BATERIA_H_

#include <Arduino.h>

void  pinoBateria(int pinoBateria);
void  leituraPinoBateria();
float tensaoBateria();
int   porcentBateria();

#endif