//
// WF32M - all in One TFT LCD Displays (Clever System) example
// for use with Software Serial
// 

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