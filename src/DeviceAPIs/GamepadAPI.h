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

#include "DescriptorPrimitives.h"


#define DESCRIPTOR_GAMEPAD_BUTTONS   \
  /* 32 Buttons */   \
  D_USAGE_PAGE, D_PAGE_BUTTON,							/*   USAGE_PAGE (Button) */   \
  D_USAGE_MINIMUM, 0x01,							/*   USAGE_MINIMUM (Button 1) */   \
  D_USAGE_MAXIMUM, 0x20,							/*   USAGE_MAXIMUM (Button 32) */   \
  D_LOGICAL_MINIMUM, 0x00,							/*   _LOGICAL_MINIMUM (0) */   \
  D_LOGICAL_MAXIMUM, 0x01,							/*   _LOGICAL_MAXIMUM (1) */   \
  D_REPORT_SIZE, 0x01,							/*   REPORT_SIZE (1) */   \
  D_REPORT_COUNT, 0x20,							/*   REPORT_COUNT (32) */   \
  D_INPUT, (D_DATA|D_VARIABLE|D_ABSOLUTE),							/*   INPUT (Data,Var,Abs) */  




#define DESCRIPTOR_GAMEPAD_4AXIS   \
  /* 4 16bit Axis */   \
  D_USAGE_PAGE, D_PAGE_GENERIC_DESKTOP,							/*   USAGE_PAGE (Generic Desktop) */   \
  D_COLLECTION, D_PHYSICAL,							/*   COLLECTION (Physical) */   \
  D_USAGE, 0x30,							/*     USAGE (X) */   \
  D_USAGE, 0x31,							/*     USAGE (Y) */   \
  D_USAGE, 0x33,							/*     USAGE (Rx) */   \
  D_USAGE, 0x34,							/*     USAGE (Ry) */   \
  D_MULTIBYTE(D_LOGICAL_MINIMUM), 0x00, 0x80,					/*     _LOGICAL_MINIMUM (-32768) */   \
  D_MULTIBYTE(D_LOGICAL_MAXIMUM), 0xFF, 0x7F,					/*     _LOGICAL_MAXIMUM (32767) */   \
  D_REPORT_SIZE, 0x10,							/*     REPORT_SIZE (16) */   \
  D_REPORT_COUNT, 0x04,							/*     REPORT_COUNT (4) */   \
  D_INPUT, (D_DATA|D_VARIABLE|D_ABSOLUTE),							/*     INPUT (Data,Var,Abs) */   \

#define DESCRIPTOR_GAMEPAD_2AXIS   \
  /* 2 8bit Axis */   \
  D_USAGE, 0x32,							/*     USAGE (Z) */   \
  D_USAGE, 0x35,							/*     USAGE (Rz) */   \
  D_LOGICAL_MINIMUM, 0x80,							/*     _LOGICAL_MINIMUM (-128) */   \
  D_LOGICAL_MAXIMUM, 0x7F,							/*     _LOGICAL_MAXIMUM (127) */   \
  D_REPORT_SIZE, 0x08,							/*     REPORT_SIZE (8) */   \
  D_REPORT_COUNT, 0x02,							/*     REPORT_COUNT (2) */   \
  D_INPUT, (D_DATA|D_VARIABLE|D_ABSOLUTE),							/*     INPUT (Data,Var,Abs) */   \
  D_END_COLLECTION,								/*   END_COLLECTION */   

#define DESCRIPTOR_GAMEPAD_HAT_SWITCHES   \
  /* 2 Hat Switches */   \
  D_USAGE_PAGE, D_PAGE_GENERIC_DESKTOP,							/*   USAGE_PAGE (Generic Desktop) */   \
  D_USAGE, 0x39,							/*   USAGE (Hat switch) */   \
  D_USAGE, 0x39,							/*   USAGE (Hat switch) */   \
  D_LOGICAL_MINIMUM, 0x01,							/*   _LOGICAL_MINIMUM (1) */   \
  D_LOGICAL_MAXIMUM, 0x08,							/*   _LOGICAL_MAXIMUM (8) */   \
  D_REPORT_COUNT, 0x02,							/*   REPORT_COUNT (2) */   \
  D_REPORT_SIZE, 0x04,							/*   REPORT_SIZE (4) */   \
  D_INPUT, (D_DATA|D_VARIABLE|D_ABSOLUTE),							/*   INPUT (Data,Var,Abs) */   \
  D_END_COLLECTION								/* END_COLLECTION */   

// Dpad directions
#define GAMEPAD_DPAD_CENTERED 0
#define GAMEPAD_DPAD_UP 1
#define GAMEPAD_DPAD_UP_RIGHT 2
#define GAMEPAD_DPAD_RIGHT 3
#define GAMEPAD_DPAD_DOWN_RIGHT 4
#define GAMEPAD_DPAD_DOWN 5
#define GAMEPAD_DPAD_DOWN_LEFT 6
#define GAMEPAD_DPAD_LEFT 7
#define GAMEPAD_DPAD_UP_LEFT 8


typedef union {
  // 32 Buttons, 6 Axis, 2 D-Pads
  uint32_t buttons;

  struct {
    uint8_t button1 : 1;
    uint8_t button2 : 1;
    uint8_t button3 : 1;
    uint8_t button4 : 1;
    uint8_t button5 : 1;
    uint8_t button6 : 1;
    uint8_t button7 : 1;
    uint8_t button8 : 1;

    uint8_t button9 : 1;
    uint8_t button10 : 1;
    uint8_t button11 : 1;
    uint8_t button12 : 1;
    uint8_t button13 : 1;
    uint8_t button14 : 1;
    uint8_t button15 : 1;
    uint8_t button16 : 1;

    uint8_t button17 : 1;
    uint8_t button18 : 1;
    uint8_t button19 : 1;
    uint8_t button20 : 1;
    uint8_t button21 : 1;
    uint8_t button22 : 1;
    uint8_t button23 : 1;
    uint8_t button24 : 1;

    uint8_t button25 : 1;
    uint8_t button26 : 1;
    uint8_t button27 : 1;
    uint8_t button28 : 1;
    uint8_t button29 : 1;
    uint8_t button30 : 1;
    uint8_t button31 : 1;
    uint8_t button32 : 1;

    int16_t	xAxis;
    int16_t	yAxis;

    int16_t	rxAxis;
    int16_t	ryAxis;

    int8_t	zAxis;
    int8_t	rzAxis;

    uint8_t	dPad1 : 4;
    uint8_t	dPad2 : 4;
  };
} HID_GamepadReport_Data_t;

class GamepadAPI {
 public:
  inline GamepadAPI(void);

  inline void begin(void);
  inline void end(void);
  inline void write(void);
  inline void press(uint8_t b);
  inline void release(uint8_t b);
  inline void releaseAll(void);

  inline void buttons(uint32_t b);
  inline void xAxis(int16_t a);
  inline void yAxis(int16_t a);
  inline void zAxis(int8_t a);
  inline void rxAxis(int16_t a);
  inline void ryAxis(int16_t a);
  inline void rzAxis(int8_t a);
  inline void dPad1(int8_t d);
  inline void dPad2(int8_t d);

  virtual void sendReport(void* data, int length);
 protected:
  HID_GamepadReport_Data_t _report;
};

#include "GamepadAPI.hpp"
