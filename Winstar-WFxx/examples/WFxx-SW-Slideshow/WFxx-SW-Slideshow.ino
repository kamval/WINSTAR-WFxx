/*
MIT License

Copyright (c) 2019 Kamen Valkov 

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

// WF32M - all in One TFT LCD Displays (Clever System) example
// for use with Software Serial

#include <Winstar-WFxx.h>
#include <SoftwareSerial.h> 

#define RX_PIN 10  //RX of WF32M
#define TX_PIN 11  //TX of WF32M

SoftwareSerial WFxxSerial(RX_PIN, TX_PIN); //RX, TX

WFxx WF32M(WFxxSerial);

void setup() {

  WFxxSerial.begin(19200);
  delay(50);
}

void loop() {

  WF32M.Picture_Command(3,0,0,0,0);
  delay(1000);
  WF32M.Picture_Command(3,0,0,0,1);
  delay(1000);
  WF32M.Picture_Command(3,0,0,0,2);
  delay(1000);
  WF32M.Picture_Command(3,0,0,0,3);
  delay(1000);
  WF32M.Picture_Command(3,0,0,0,4);
  delay(1000);
}