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

#include "ConsumerControl.h"
#include "DescriptorPrimitives.h"

static const uint8_t _hidMultiReportDescriptorConsumer[] PROGMEM = {
  /* Consumer Control (Sound/Media keys) */
  D_USAGE_PAGE, 0x0C,									/* usage page (consumer device) */
  D_USAGE, 0x01, 								/* usage -- consumer control */
  D_COLLECTION, D_APPLICATION, 								/* collection (application) */
  D_REPORT_ID, HID_REPORTID_CONSUMERCONTROL, 		/* report id */
   
  DESCRIPTOR_CONSUMER_CONTROL_KEYS

  D_END_COLLECTION /* end collection */
};

ConsumerControl_::ConsumerControl_(void) {
  static HIDSubDescriptor node(_hidMultiReportDescriptorConsumer, sizeof(_hidMultiReportDescriptorConsumer));
  HID().AppendDescriptor(&node);
}

void ConsumerControl_::sendReport(void* data, int length) {
  HID().SendReport(HID_REPORTID_CONSUMERCONTROL, data, length);
}

ConsumerControl_ ConsumerControl;
