/**************************************************************************/
/*  serial.cpp                                                            */
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

#include "serial.h"

uint8_t count = 0;
bool configMode = true;
char flowBuffer[FLOW_BUFFER_SIZE];
char configBuffer[CONFIG_BUFFER_SIZE];
static uint16_t pumpConfig[3];

static void serialize(uint8_t *array, size_t length) {
    flowBuffer[0] = '\0';
    for (int i = 0; i < length; ++i) {
        sprintf(flowBuffer + strlen(flowBuffer), "%d", array[i]);
        if (i != length - 1) {
            sprintf(flowBuffer + strlen(flowBuffer), ",");
        }
    }
}

static void deserialize(char *stream, uint8_t *values) {
    uint8_t idx = 0;
    char *token = strtok(stream, ",");
    while (token != NULL) {
        values[idx++] = (uint8_t)atoi(token);
        token = strtok(NULL, ",");
    }
}

static void deserialize(char *stream, uint16_t *values) {
    uint8_t idx = 0;
    char *token = strtok(stream, ",");
    while (token != NULL) {
        values[idx++] = (uint16_t)atoi(token);
        token = strtok(NULL, ",");
    }
}

void initializeSerial() {
    Serial.begin(BAUD_RATE);
    while (!Serial) {
        ;
    }
}

void readFlowProfile() {
    if (Serial.available() > 0) {
        char received = (char)Serial.read();
        if (received == PUMP_CONFIG_END_CHAR) {
            count = 0;
            configMode = false;
            deserialize(configBuffer, pumpConfig);
            setPumpConfig(pumpConfig[0], pumpConfig[1], pumpConfig[2]);
            return;
        }
        if (received == FLOW_PROFILE_END_FLAG) {
            deserialize(flowBuffer, targetFlowRate);
            readMode = false;
            count = 0;
            blink();
            return;
        }
        if (configMode)
            configBuffer[count++] = received;
        else
            flowBuffer[count++] = received;
    }
}

void writeFlowRates(uint8_t *measuredFlowRate) {
    serialize(measuredFlowRate, N_FLOW_POINTS);
    Serial.println(flowBuffer);
}
