/**
* File: patchugino_relay.h
* Created on: 2025-08-04 at 16:35
* Author: Andrea Rantin
* Description: This file contains the class Patchugino_Relay that is the class used for
* managing the Patchugino_Relay board. It allows to initialize the board with the specified I2C address and control
* any of the 6 relays of the board
*/

#pragma once

#include "patchugo_core.h"
#include "internal/patchugo_relay_types.h"
#include <Wire.h>

using namespace PatchuginoRelay;

class Patchugino_Relay {
    private:
        int usedI2CAddr; /*<! I2C Address used for communication. Selected from H10,H11,H12 pin headers*/
        Patchugo_Logger* logger = nullptr;
        /**
        * @brief Reads the current state of all relays
        * 
        * @return uint8_t State of all relays
        */
        PatchugoStatusCode ReadRelayState(uint8_t *relayState);
    public:
        /**
        * @brief Initializes the Patchugino_Relay board
        * 
        * @param i2cAddr I2C Address to use for the board(Selected from H10,H11,H12 pin headers)
        * @param serial Serial used for logging of Patchugino_Relay. Defaults to Serial
        * @param logLevel Logging level used for logging of Patchugino_Relay. Defaults to LOG_LEVEL_VERBOSE
        * 
        * @note The serial instance must be initialized by calling Serial.begin before calling this Init function, otherwise logs
        * will not be visible!
        */
        void Init(PatchuginoRelayI2CAddr i2cAddr, HardwareSerial& serial = Serial, PatchugoLogLevel logLevel = LOG_LEVEL_VERBOSE);

        /**
        * @brief Writes the given state to the selected relay
        * 
        * @param relayN Relay to write. This is a value of @ref PatchugoRelayN
        * @param state State to write. This is a value of @ref PatchugoRelayN
        * @return PatchugoStatusCode //TODO
        */
        PatchugoStatusCode Write(PatchugoRelayN relayN, PatchugoRelayState state);

        /**
        * @brief Sets all the relays of the board to 0
        * 
        * @return PatchugoStatusCode //TODO
        * 
        * @note It is suggested to call this function in the Setup of any firmware so that the relays never start in
        * an undefined state
        */
        PatchugoStatusCode Clear(void);

        /**
        * @brief Reads the status of one of the relays given its number
        * 
        * @param relayN Relay to read
        * @param readState State of the relay
        * @return PatchugoStatusCode //TODO
        */
        PatchugoStatusCode Read(PatchugoRelayN relayN, PatchugoRelayState *readState);

        /**
        * @brief Reads the status of one of the relays given its number
        * 
        * @param relayN Relay to read
        * @param readState State of the relay
        * @return PatchugoStatusCode //TODO
        */
        PatchugoStatusCode Read(PatchugoRelayN relayN, uint8_t *readState);
};
