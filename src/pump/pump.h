/**************************************************************************/
/*  pump.h                                                                */
/**************************************************************************/
/*                          Author: Atick Faisal                          */
/*                           https://atick.dev/                           */
/**************************************************************************/
/* Copyright (c) 2023-present Atick Faisal                                */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#ifndef PUMP_H
#define PUMP_H

#include <AccelStepper.h>

#include "../config/config.h"
#include "../flow/flow.h"
#include "../serial/serial.h"
#include "../utils/utils.h"

extern bool readMode;
extern uint8_t targetFlowRate[N_FLOW_POINTS];
extern uint8_t measuredFlowRate[N_FLOW_POINTS];

enum PumpType { SYRINGE, PERILSTALTIC };

struct PumpConfig {
    PumpType pumpType;
    uint16_t flowPeriod;
    uint16_t chipDiameter;
};

void initializeMotors();
void initializeHomeSwitches();
void controlPump();
void setPumpConfig(uint8_t pumpType, uint16_t flowPeriod,
                   uint16_t chipDiameter);

#endif