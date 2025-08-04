/**
* File: patchugo_relay_types.h
* Created on: 2025-08-04 at 16:38
* Author: Andrea Rantin
* Description: his file contains definitions for the Patchugino_Analog library,
* such as I2C addresses and relay definitions
*/

#pragma once

#include <Arduino.h>

namespace PatchuginoRelay {

    /**
    * @brief Possible I2C addresses to select.
    * To see the addresses table you can consult datasheet
    * of PCF8574 at page 14
    */
    enum class PatchuginoRelayI2CAddr {
        I2C_ADDR_1 = (0x20U),
        I2C_ADDR_2 = (0x21U),
        I2C_ADDR_3 = (0x22U),
        I2C_ADDR_4 = (0x23U),
        I2C_ADDR_5 = (0x24U),
        I2C_ADDR_6 = (0x25U),
        I2C_ADDR_7 = (0x26U),
        I2C_ADDR_8 = (0x27U),
    };

    //Utility constant expressions to ease use of enum class of PatchuginoRelayI2CAddr
    static constexpr PatchuginoRelayI2CAddr PATCHUGINO_RELAY_ADDR_1 = PatchuginoRelayI2CAddr::I2C_ADDR_1;
    static constexpr PatchuginoRelayI2CAddr PATCHUGINO_RELAY_ADDR_2 = PatchuginoRelayI2CAddr::I2C_ADDR_2;
    static constexpr PatchuginoRelayI2CAddr PATCHUGINO_RELAY_ADDR_3 = PatchuginoRelayI2CAddr::I2C_ADDR_3;
    static constexpr PatchuginoRelayI2CAddr PATCHUGINO_RELAY_ADDR_4 = PatchuginoRelayI2CAddr::I2C_ADDR_4;
    static constexpr PatchuginoRelayI2CAddr PATCHUGINO_RELAY_ADDR_5 = PatchuginoRelayI2CAddr::I2C_ADDR_5;
    static constexpr PatchuginoRelayI2CAddr PATCHUGINO_RELAY_ADDR_6 = PatchuginoRelayI2CAddr::I2C_ADDR_6;
    static constexpr PatchuginoRelayI2CAddr PATCHUGINO_RELAY_ADDR_7 = PatchuginoRelayI2CAddr::I2C_ADDR_7;
    static constexpr PatchuginoRelayI2CAddr PATCHUGINO_RELAY_ADDR_8 = PatchuginoRelayI2CAddr::I2C_ADDR_8;

    /**
    * @brief Enum representing the 6 relays present on board.
    * Relay 1 corresponds to value 0, Relay 2 to 1 and so on
    */
    enum class PatchugoRelayN {
        RELAY_1 = 0,
        RELAY_2,
        RELAY_3,
        RELAY_4,
        RELAY_5,
        RELAY_6,
    };

    //Utility constant expressions to ease use of enum class of PatchugoRelayN
    static constexpr PatchugoRelayN PATCHUGINO_RELAY_N_1 = PatchugoRelayN::RELAY_1;
    static constexpr PatchugoRelayN PATCHUGINO_RELAY_N_2 = PatchugoRelayN::RELAY_2;
    static constexpr PatchugoRelayN PATCHUGINO_RELAY_N_3 = PatchugoRelayN::RELAY_3;
    static constexpr PatchugoRelayN PATCHUGINO_RELAY_N_4 = PatchugoRelayN::RELAY_4;
    static constexpr PatchugoRelayN PATCHUGINO_RELAY_N_5 = PatchugoRelayN::RELAY_5;
    static constexpr PatchugoRelayN PATCHUGINO_RELAY_N_6 = PatchugoRelayN::RELAY_6;

    /**
    * @brief State writable or readable from the relays(0 or 1)
    * 
    */
    enum class PatchugoRelayState {
        RELAY_STATE_RESET,
        RELAY_STATE_SET,
    };

    //Utility constant expressions to ease use of enum class of PatchugoRelayState
    static constexpr PatchugoRelayState PATCHUGINO_RELAY_RESET = PatchugoRelayState::RELAY_STATE_RESET;
    static constexpr PatchugoRelayState PATCHUGINO_RELAY_SET = PatchugoRelayState::RELAY_STATE_SET;
}

