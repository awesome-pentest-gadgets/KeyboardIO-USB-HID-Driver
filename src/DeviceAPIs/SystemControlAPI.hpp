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

#pragma once

SystemControlAPI::SystemControlAPI(void) {}

void SystemControlAPI::begin(void) {
  // release all buttons
  end();
}

void SystemControlAPI::end(void) {
  uint8_t _report = 0x00;
  sendReport(&_report, sizeof(_report));
}

void SystemControlAPI::write(uint8_t s) {
  press(s);
  release();
}

void SystemControlAPI::release(void) {
  begin();
}

void SystemControlAPI::releaseAll(void) {
  begin();
}

void SystemControlAPI::press(uint8_t s) {
  if (s == HID_SYSTEM_WAKE_UP)
    USBDevice.wakeupHost();
  else
    sendReport(&s, sizeof(s));
}


