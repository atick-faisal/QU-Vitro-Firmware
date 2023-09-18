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

#ifndef PUMP_H
#define PUMP_H

#include "../config/config.h"
#include "../flow/flow.h"
#include "../serial/serial.h"
#include "../utils/utils.h"

extern bool readMode;
extern uint8_t flowProfile[N_FLOW_POINTS];
extern uint8_t flowRates[N_FLOW_POINTS];

void initializePump();
void controlPump();

#endif