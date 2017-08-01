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


void NKROKeyboardAPI::begin(void) {
  // Force API to send a clean report.
  // This is important for and HID bridge where the receiver stays on,
  // while the sender is resetted.
  releaseAll();
  sendReport();
}

void NKROKeyboardAPI::end(void) {
   begin();
}

NKROKeyboardAPI::NKROKeyboardAPI(void) {}

boolean NKROKeyboardAPI::isModifierActive(uint8_t k) {
  if (isModifierKey(k)) {
    k = k - HID_KEYBOARD_FIRST_MODIFIER;
    return !!(_keyReport.modifiers & (1 << k));
  }
  return false;
}

boolean NKROKeyboardAPI::isModifierKey(uint8_t k) {
  if (k >= HID_KEYBOARD_FIRST_MODIFIER && k <= HID_KEYBOARD_LAST_MODIFIER) {
	return true;
  }
  return false;
}

size_t NKROKeyboardAPI::press(uint8_t k) {
  // If the key is in the range of 'printable' keys
  if (k <= HID_LAST_KEY) {
    uint8_t bit = 1 << (uint8_t(k) % 8);
    _keyReport.keys[k / 8] |= bit;
    return 1;
  }

  // It's a modifier key
  else if (isModifierKey(k)) {
    // Convert key into bitfield (0 - 7)
    k = k - HID_KEYBOARD_FIRST_MODIFIER;
    _keyReport.modifiers |= (1 << k);
    return 1;
  }

  // No empty/pressed key was found
  return 0;
}

size_t NKROKeyboardAPI::release(uint8_t k) {
  // If we're releasing a printable key
  if (k <= HID_LAST_KEY) {
    uint8_t bit = 1 << (k % 8);
    _keyReport.keys[k / 8] &= ~bit;
    return 1;
  }

  // It's a modifier key
  else if (isModifierKey(k)) {
    // Convert key into bitfield (0 - 7)
    k = k - HID_KEYBOARD_FIRST_MODIFIER;
    _keyReport.modifiers &= ~(1 << k);
    return 1;
  }

  // No empty/pressed key was found
  return 0;
}

void NKROKeyboardAPI::releaseAll(void) {
  // Release all keys
  _lastKeyReport.allkeys[0]=1; //force there to be a change to make sure the guard code runs
  memset(&_keyReport.allkeys, 0x00, sizeof(_keyReport.allkeys));
}


