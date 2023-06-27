#ifndef PUMP_H
#define PUMP_H

#include "../config/config.h"
#include "../flow/flow.h"
#include "../utils/utils.h"

extern bool readMode;
extern uint8_t flowProfile[N_FLOW_POINTS];

void initializePump();
void controlPump();

#endif