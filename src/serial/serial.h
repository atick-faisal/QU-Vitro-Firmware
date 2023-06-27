#ifndef SERIAL_H
#define SERIAL_H

#include "../utils/utils.h"
#include "../config/config.h"

const unsigned long BAUD_RATE = 115200;

extern bool readMode;
extern uint8_t flowProfile[N_FLOW_POINTS];

void initializeSerial();
void readFlowProfile();
void writeFlowProfile();

#endif