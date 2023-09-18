/**************************************************************************/
/*  config.h                                                              */
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