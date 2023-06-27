#include "pump/pump.h"
#include "serial/serial.h"
#include "utils/utils.h"

bool readMode = false;

void setup() {
    initializeUtils();
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