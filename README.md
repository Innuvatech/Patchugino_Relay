# Patchugino_Relay
Arduino library for Patchugino_Relay shield board

## Getting Started
This library allows to control the Patchugino_Relay shield board which can be mounted on top of a PatchugoLite board. It is therefore necessary to have
the Patchugo Boards package installed from [Arduino Boards Manager](https://docs.arduino.cc/learn/starting-guide/cores/). 

If you have not done that already, add this link in the "_Additional Boards Managers URLs_" in Arduino preferences:

https://github.com/Innuvatech/BoardManagerFiles/raw/main/package_innuvatech_index.json

## Board Description
The Patchugino_Relay board is a shield board that can be plugged on top of a PatchugoLite board. It allows to control up to 6 relays of trough an I2C/GPIO expander. Many I2C addresses for the expander can be selected with
H10, H11 and H12 pin headers, making thus possible to use many Patchugino_Relay boards together.

### Power Supply
The board does not need any additional wiring for its power supply. It powers itself by being plugged on top of a PatchugoLite

## Library Usage
The arduino library allows to control the board in a really simple and intuitive way with just a few lines of code. It allows to initialize the board by specifying which I2C address is being used from H10, H11 and H12.
It allows to READ/WRITE each relay as well as resetting all of them with a dedicated command.

### Initialization
The library provides and Initialization function called **Init** that allows to initialize everything that the board needs in order to work. The function takes the following parameters as input:
  - **i2cAddr**: The I2C address that has been selected from the pinheaders. The I2C addresses configuration can be seen down below
  - **serial(optional)**: This is an optional parameter. It specifies the Serial instance used by the internal logs of the library. If not provided this parameter defaults to the default Serial instance of the                     PatchugoLite board
  - **logLevel(optional)**: This specifies the logging level of the library. Setting a higher logging level means more logs from the library will be shown. Logs from the library can be disabled by setting this to                   **LOG_LEVEL_NONE**. For more information about logging please consult the [Patchugo_Core](https://github.com/Innuvatech/Patchugo_Core) repository

#### I2C Addresses configuration table
| Definition name | H10 | H11 | H12 | I2C Address |
| ----------------| ----| ----| ----| ------------|
| PATCHUGINO_RELAY_ADDR_1 | TO PGND | TO PGND | TO PGND | 0x20 |
| PATCHUGINO_RELAY_ADDR_2 | TO 5V | TO PGND | TO PGND | 0x21 |
| PATCHUGINO_RELAY_ADDR_3 | TO PGND | TO 5V | TO PGND | 0x22 |
| PATCHUGINO_RELAY_ADDR_4 | TO 5V | TO 5V | TO PGND | 0x23 |
| PATCHUGINO_RELAY_ADDR_5 | TO PGND | TO PGND | TO 5V | 0x24 |
| PATCHUGINO_RELAY_ADDR_6 | TO 5V | TO PGND | TO 5V | 0x25 |
| PATCHUGINO_RELAY_ADDR_7 | TO PGND | TO 5V | TO 5V | 0x26 |
| PATCHUGINO_RELAY_ADDR_8 | TO 5V | TO 5V | TO 5V | 0x27 |

Examples of initialization are provided below:

#### Minimal initialization

```
  /*
    IMPORTANT!!! Patchugino Relay library needs
    Serial instance to be initialized before calling any function!
  */
  Serial.begin(115200);

  //Initialize the Relay shield board and specify which I2C address it's using(0x20 in this case)
  //Since serial and logLevel are not specified this will default to using Serial with LOG_LEVEL_VERBOSE
  patchuginoRelay.Init(PATCHUGINO_RELAY_ADDR_1);
```

#### Custom logging initialization
```
  /*
    IMPORTANT!!! Patchugino Relay library needs
    Serial instance to be initialized before calling any function!
  */
  HardwareSerial mySerial(PA10, PA11);
  
  //Initialize the Relay shield board and specify which I2C address it's using(0x20 in this case)
  //This will use mySerial as logs output channel and will only show DEBUG level logs or lower
  patchuginoRelay.Init(PATCHUGINO_RELAY_ADDR_1, mySerial, LOG_LEVEL_DEBUG);
```
#### No logging initialization
```
void setup() {
  /*
    IMPORTANT!!! Patchugino Relay library needs
    Serial instance to be initialized before calling any function!
  */
  Serial.begin(115200);
  
  //Initialize the Relay shield board and specify which I2C address it's using(0x20 in this case)
  //This will disable logs of the library. A valid Serial instance still needs to be provided
   patchuginoRelay.Init(PATCHUGINO_RELAY_ADDR_1, Serial, LOG_LEVEL_NONE);
```

### Writing and reading a relay
To set/reset a relay the **Write** must be called. The function takes the following parameters:
  - relayN: The relay number of the relay to write. A table of all relays numers is provided below
  - state: State to write to the relay(0 or 1). The following definitions can be passed as state:
      - PATCHUGINO_RELAY_RESET: This corresponds to a logical 0
      - PATCHUGINO_RELAY_SET: This corresponds to a logical 1
      - 
  This function returns a **PatchugoStatusCode** enum value. Anything other than the code OK is to be considered as an error/failure. For more information about error codes please consult  
  the [Patchugo_Core](https://github.com/Innuvatech/Patchugo_Core) repository
   
An example of writing to relays is provided below
```
  //Writes 1 to the relay 1
  if(patchuginoRelay.Write(PATCHUGINO_RELAY_N_1, PATCHUGINO_RELAY_SET) != OK) {
    Serial.println("ERROR WRITE");
    //Manage your error here
  }
  //Writes 0 to the relay 2
  if(patchuginoRelay.Write(PATCHUGINO_RELAY_N_2, PATCHUGINO_RELAY_RESET) != OK) {
    Serial.println("ERROR WRITE");
    //Manage your error here
  }
```
   
To read a relay the **Read** function must be called. The function takes the following parameters:
  - relayN: The relay number of the relay to write. A table of all relays numers is provided below
  - readState: Pointer to the value that is read from the relay(0 or 1). This can be either of a plain uint8_t type
    or it can also be a pointer to a PatchugoRelayState definition.

 This function returns a **PatchugoStatusCode** enum value. Anything other than the code OK is to be considered as an error/failure. For more information about error codes please consult  
 the [Patchugo_Core](https://github.com/Innuvatech/Patchugo_Core) repository

An example of reading relays is provided below:
```
  //Reads relay 3 state and puts it into myRead
  uint8_t myRead = 0;
  if(patchuginoRelay.Read(PATCHUGINO_RELAY_N_3, &myRead) != OK) {
    Serial.println("ERROR READ");
    //Manage your error here
  }

  //Reads relay 4 state and puts it into myState
  PatchugoRelayState myState;
  if(patchuginoRelay.Read(PATCHUGINO_RELAY_N_4, &myState) != OK) {
    Serial.println("ERROR READ");
    //Manage your error here
  }
```

A function to reset all relays is also available. The function takes no parameters and an example is provided below:
```
  //Sets all relays to 0
  if(patchuginoRelay.Clear() != OK) {
    Serial.println("ERROR CLEAR");
    //Manage your error here
  }
```
