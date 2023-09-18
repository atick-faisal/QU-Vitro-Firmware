#include "pump/pump.h"
#include "serial/serial.h"
#include "utils/utils.h"

bool readMode = false;

void setup() {
    initializePins();
    initializePump();
    initializeSerial();
}

void loop() {
    if (readMode) {
        readFlowProfile();
    } else {
        controlPump();
    }
}