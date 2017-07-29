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

#include "Gamepad.h"
#include "DescriptorPrimitives.h"

static const uint8_t _hidMultiReportDescriptorGamepad[] PROGMEM = {
  /* Gamepad with 32 buttons and 6 axis*/
  D_USAGE_PAGE, D_PAGE_GENERIC_DESKTOP,							/* USAGE_PAGE (Generic Desktop) */
  D_USAGE, D_USAGE_JOYSTICK,							/* USAGE (Joystick) */
  D_COLLECTION, D_APPLICATION,							/* COLLECTION (Application) */
  D_REPORT_ID, HID_REPORTID_GAMEPAD,			/*   REPORT_ID */
  DESCRIPTOR_GAMEPAD_BUTTONS
  DESCRIPTOR_GAMEPAD_4AXIS
  DESCRIPTOR_GAMEPAD_2AXIS
  DESCRIPTOR_GAMEPAD_HAT_SWITCHES
};

Gamepad_::Gamepad_(void) {
  static HIDSubDescriptor node(_hidMultiReportDescriptorGamepad, sizeof(_hidMultiReportDescriptorGamepad));
  HID().AppendDescriptor(&node);
}

void Gamepad_::sendReport(void* data, int length) {
  HID().SendReport(HID_REPORTID_GAMEPAD, data, length);
}

Gamepad_ Gamepad;
