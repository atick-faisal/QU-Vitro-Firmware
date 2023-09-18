// Copyright 2023 Atick Faisal

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef SERIAL_H
#define SERIAL_H

#include "../config/config.h"
#include "../utils/utils.h"

const unsigned long BAUD_RATE = 115200;

extern bool readMode;
extern uint8_t flowProfile[N_FLOW_POINTS];

void initializeSerial();
void readFlowProfile();
void writeFlowRates(uint8_t *flowRates);

#endif