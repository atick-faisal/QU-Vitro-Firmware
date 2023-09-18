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
char buffer[BUFFER_SIZE];

static void serialize(uint8_t *array, size_t length) {
    buffer[0] = '\0';
    for (int i = 0; i < length; ++i) {
        sprintf(buffer + strlen(buffer), "%d", array[i]);
        if (i != length - 1) {
            sprintf(buffer + strlen(buffer), ",");
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

void initializeSerial() {
    Serial.begin(BAUD_RATE);
    while (!Serial) {
        ;
    }
}

void readFlowProfile() {
    if (Serial.available() > 0) {
        char received = (char)Serial.read();
        if (received == FLOW_PROFILE_END_FLAG) {
            deserialize(buffer, flowProfile);
            readMode = false;
            count = 0;
            blink();
            return;
        }
        buffer[count++] = received;
    }
}

void writeFlowRates(uint8_t *flowRates) {
    serialize(flowRates, N_FLOW_POINTS);
    Serial.println(buffer);
}
