#ifndef PINS_MIGHTYBOARD_REVH_H
#define PINS_MIGHTYBOARD_REVH_H

#include <Arduino.h>

// =========================================================================
// 🎛️ MOSFET, BUZZER, AND RELAY OUTPUTS (Verified Mappings)
// =========================================================================
#define MB_BUZZER_PIN       6   // Onboard Piezo audio buzzer
// #define MB_LED_EXTRUDER     7   // LED indicator located by Extruder driver
// #define MB_HEATED_BED       8   // High-power Heatbed MOSFET terminal
#define MB_FAN_PIN          4   // Cooling Fan MOSFET terminal

// =========================================================================
// 🏎️ STEPPER MOTOR CONTROL PINS (Verified Stepper Layout)
// =========================================================================
//#define STEPPERS_ENABLE_PIN 38  // Global Buffer Enable (Pull LOW to wake drivers)


// X-Axis Stepper Channel
//#define X_STEP_PIN         42  
//#define X_DIR_PIN          41  

// Y-Axis Stepper Channel
#define Y_STEP_PIN         44 
#define Y_DIR_PIN          42  
#define Y_ENABLE           45

// Z-Axis Stepper Channel (FIXED: Direction shifted back to 49)
#define Z_STEP_PIN         48  
#define Z_DIR_PIN          47 
#define Z_ENABLE           49 

// Extruder A Motor Channel
//#define E1_STEP_PIN        44  
//#define E1_DIR_PIN         43  

// Extruder B Motor Channel
//#define E2_STEP_PIN        48  
//#define E2_DIR_PIN         47  

// =========================================================================
// 🛑 ENDSTOPS / LIMIT SWITCH INPUTS (Verified by Test)
// =========================================================================
#define X_STOP_PIN         32   // True X-Stop
#define Y_STOP_PIN         31   // True Y-Stop
#define Z_STOP_PIN         30   // True Z-Stop

// =========================================================================
// 🎨 RGB CASE LIGHTING LINES (PWM Capable)
// =========================================================================
//#define RGB_RED_PIN        32
//#define RGB_GREEN_PIN      31
//#define RGB_BLUE_PIN       30

// =========================================================================
// 🌡️ TEMPERATURE / THERMOCOUPLE SPI SENSORS
// =========================================================================
// #define TC1_CS_PIN         18   // Thermocouple 1 Chip Select
// #define TC2_CS_PIN         19   // Thermocouple 2 Chip Select
// #define TC_SCK_PIN         52   // Shared Hardware SPI Clock
// #define TC_MISO_PIN        50   // Shared Hardware SPI Data Out

// =========================================================================
// 💾 ONBOARD SD CARD SLOT LOGIC (SPI)
// =========================================================================
// #define SD_SS_PIN          53   // SD Card Slave Select
// #define SD_DETECT_PIN      49   // Physical card insertion detection pin

#endif // PINS_MIGHTYBOARD_REVH_H

