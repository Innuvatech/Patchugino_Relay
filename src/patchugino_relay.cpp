/**
* File: patchugino_relay.cpp
* Created on: 2025-08-04 at 16:48
* Author: Andrea Rantin
* Description: Implementation file for patchugino_relay.h
*/

#include "patchugino_relay.h"

PatchugoStatusCode Patchugino_Relay::ReadRelayState(uint8_t *relayState) {

    Wire.requestFrom(usedI2CAddr, (uint8_t)1);
    if(!Wire.available()) return ERROR_RELAY_READ_STATE;
    *relayState = Wire.read();
    return OK;
}

void Patchugino_Relay::Init(PatchuginoRelayI2CAddr i2cAddr, HardwareSerial& serial, PatchugoLogLevel logLevel) {
    
    //Initialize logger
    static Patchugo_Logger localLogger(serial, logLevel);
    logger = &localLogger;

    logger->Log_Info("Patchugino Relay initializing\n");

    //Set I2C address used for communication with I2C expander
    usedI2CAddr = static_cast<int>(i2cAddr);

    logger->Log_Verbose("Using I2C Addr: %ld\n", usedI2CAddr);

    Wire.end();
    Wire.begin();

    logger->Log_Info("Patchugino Relay initialized\n");
}

PatchugoStatusCode Patchugino_Relay::Write(PatchugoRelayN relayN, PatchugoRelayState state) {

    uint8_t relayState = 0;
    PatchugoStatusCode checkError = ReadRelayState(&relayState);
    if(checkError != OK) return checkError;

    uint8_t relayNVal = static_cast<uint8_t>(relayN);
    switch(state) {
        case PatchugoRelayState::RELAY_STATE_RESET:
            relayState &= ~(0x01U << relayNVal);
            break;
        case PatchugoRelayState::RELAY_STATE_SET:
            relayState |= (0x01U << relayNVal);
            break;
        default:
            break;
    }

    Wire.beginTransmission(usedI2CAddr);
    Wire.write(relayState);
    if(Wire.endTransmission() != 0) return ERROR_RELAY_WRITE;

    return OK;
}

PatchugoStatusCode Patchugino_Relay::Clear(void) {

    Wire.beginTransmission(usedI2CAddr);
    Wire.write(0x00);
    if(Wire.endTransmission() != 0) return ERROR_RELAY_CLEAR;

    return OK;
}

PatchugoStatusCode Patchugino_Relay::Read(PatchugoRelayN relayN, PatchugoRelayState *readState) {

    uint8_t state = 0;
    PatchugoStatusCode checkError = ReadRelayState(&state);
    if(checkError != OK) return checkError;
    
    uint8_t relayNVal = static_cast<uint8_t>(relayN);

    *readState = static_cast<PatchugoRelayState>((state & (1 << relayNVal)) != 0);
    return OK;
}

PatchugoStatusCode Patchugino_Relay::Read(PatchugoRelayN relayN, uint8_t *readState) {

    uint8_t state = 0;
    PatchugoStatusCode checkError = ReadRelayState(&state);
    if(checkError != OK) return checkError;

    uint8_t relayNVal = static_cast<uint8_t>(relayN);
    *readState = (state & (1 << relayNVal) != 0);
    return OK;

}