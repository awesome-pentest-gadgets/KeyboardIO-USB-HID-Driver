/*
Copyright (c) 2014-2015 NicoHood
See the readme for credit to other people.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

// Include guard
#pragma once

#include <Arduino.h>
#include "PluggableUSB.h"
#include "HID.h"
#include "HID-Settings.h"

#include "HIDTables.h"
#include "HIDAliases.h"

#define KEY_BYTES 28

#include "DescriptorPrimitives.h"
#define DESCRIPTOR_KEYBOARD_MODIFIERS  \
  /* Key modifier byte  */ \
  D_USAGE_MINIMUM, HID_KEYBOARD_FIRST_MODIFIER,  \
  D_USAGE_MAXIMUM, HID_KEYBOARD_LAST_MODIFIER,  \
  D_LOGICAL_MINIMUM, 0x00,  \
  D_LOGICAL_MAXIMUM, 0x01,  \
  D_REPORT_SIZE, 0x01,  \
  D_REPORT_COUNT, 0x08,  \
  D_INPUT, (D_DATA|D_VARIABLE|D_ABSOLUTE),  \

  // NKRO Keyboard   
  // USB Code not within 4-49 (0x4-0x31), 51-155 (0x33-0x9B), 157-164 (0x9D-0xA4),  
  // 176-221 (0xB0-0xDD) or 224-231 (0xE0-0xE7) NKRO Mode  
  // Padding 3 bits  
  // To skip HID_KEYBOARD_NON_US_POUND_AND_TILDE,
  // which causes Linux to choke on our driver.  
#define DESCRIPTOR_KEYBOARD_BITMAP_REPORT  \
  D_REPORT_SIZE, 0x04,  \
  D_REPORT_COUNT, 0x01,  \
  D_INPUT, (D_CONSTANT),  \
  D_USAGE_MINIMUM, HID_KEYBOARD_A_AND_A,  \
  D_USAGE_MAXIMUM, HID_KEYBOARD_BACKSLASH_AND_PIPE,  \
  D_LOGICAL_MINIMUM, 0x00,  \
  D_LOGICAL_MAXIMUM, 0x01,  \
  D_REPORT_SIZE, 0x01,  \
  D_REPORT_COUNT, (HID_KEYBOARD_BACKSLASH_AND_PIPE - HID_KEYBOARD_A_AND_A)+1,  \
  D_INPUT, (D_DATA|D_VARIABLE|D_ABSOLUTE),  \
  D_REPORT_SIZE, 0x01,  /* Padding 1 bit  */ \
  D_REPORT_COUNT, 0x01, /* To skip HID_KEYBOARD_NON_US_POUND_AND_TILDE, which causes */ \
  D_INPUT, (D_CONSTANT), /*  which caused linux to choke on our driver*/  \
  D_USAGE_MINIMUM, HID_KEYBOARD_SEMICOLON_AND_COLON,  \
  D_USAGE_MAXIMUM, HID_KEYBOARD_CANCEL,  \
  D_LOGICAL_MINIMUM, 0x00,  \
  D_LOGICAL_MAXIMUM, 0x01,  \
  D_REPORT_SIZE, 0x01,  \
  D_REPORT_COUNT, (HID_KEYBOARD_CANCEL-HID_KEYBOARD_SEMICOLON_AND_COLON) +1,  \
  D_INPUT, (D_DATA|D_VARIABLE|D_ABSOLUTE),  \
  /* Padding 1 bit.  */ \
  /* To skip HID_KEYBOARD_CLEAR, which causes  */ \
  /*  Linux to choke on our driver. */ \
  D_REPORT_SIZE, 0x01,  \
  D_REPORT_COUNT, 0x01,  \
  D_INPUT, (D_CONSTANT),  \
  D_USAGE_MINIMUM, HID_KEYBOARD_PRIOR,  \
  D_USAGE_MAXIMUM, HID_KEYPAD_HEXADECIMAL,  \
  D_LOGICAL_MINIMUM, 0x00,  \
  D_LOGICAL_MAXIMUM, 0x01,  \
  D_REPORT_SIZE, 0x01,  \
  D_REPORT_COUNT, (HID_KEYPAD_HEXADECIMAL - HID_KEYBOARD_PRIOR)  +1,  \
  D_INPUT, (D_DATA|D_VARIABLE|D_ABSOLUTE),  \
  /* Padding (w bits) */ \
  D_REPORT_SIZE, 0x02,  \
  D_REPORT_COUNT, 0x01,  \
  D_INPUT, (D_CONSTANT), 


typedef union {
  // Modifiers + keymap
  struct {
    uint8_t modifiers;
    uint8_t keys[KEY_BYTES ];
  };
  uint8_t allkeys[1 + KEY_BYTES];
} HID_KeyboardReport_Data_t;



class NKROKeyboardAPI {
 public: 
  inline NKROKeyboardAPI(void);
  inline void begin(void);
  inline void end(void);

  inline size_t press(uint8_t k);
  inline size_t release(uint8_t k);
  inline void  releaseAll(void);
  virtual int sendReport(void);

  inline boolean isModifierActive(uint8_t k);

 protected:
  HID_KeyboardReport_Data_t _keyReport;
  HID_KeyboardReport_Data_t _lastKeyReport;
 private:
};

#include "NKROKeyboardAPI.hpp"
