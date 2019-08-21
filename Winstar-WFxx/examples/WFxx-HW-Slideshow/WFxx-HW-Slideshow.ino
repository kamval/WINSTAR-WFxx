//
// WF32M - all in One TFT LCD Displays (Clever System) example 
// for use with Hardware Serial
// 

#include <Winstar-WFxx.h>

WFxx WF32M(Serial1);

void setup() {

  Serial1.begin(19200);
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