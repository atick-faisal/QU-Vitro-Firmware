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

#ifndef PUMP_CONFIG
#define PUMP_CONFIG

#include <Arduino.h>

#define PWM_MODE_ESP32

// ... Peristaltic pump motor pin
#ifdef PWM_MODE_ARDUINO
const uint8_t MOTOR_PIN = 10;
#elif defined(PWM_MODE_ESP32)
const uint8_t MOTOR_PIN = 16;
#endif

// ... Buffer size for reading and writing flow profile
const uint8_t BUFFER_SIZE = 255;

// ... Number of data-points in flow profile
const uint8_t N_FLOW_POINTS = 50;

// ... Duration of one flow profile in millisecond
const uint16_t FLOW_PERIOD = 2000;

// ... Pause between each step
const uint16_t PAUSE_BETWEEN_STEPS = (uint16_t)(FLOW_PERIOD / N_FLOW_POINTS);

// ... Start and end char of flow profile
// ... e.g. <0,1,4,...,255,....>
const char FLOW_PROFILE_START_FLAG = '<';
const char FLOW_PROFILE_END_FLAG = '>';

#ifdef ESP32
const uint8_t PWM_CHANNEL = 1;
const double PWM_FREQUENCY = 5000;
const uint8_t PWM_RESOLUTION = 8;
#endif

#endif