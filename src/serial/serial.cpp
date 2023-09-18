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
