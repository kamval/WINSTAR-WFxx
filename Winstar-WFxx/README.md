### Winstar Clever System Arduino Library

Simple arduino library, showing the main capabilities of Winstar [M Series](https://www.winstar.com.tw/products/tft-lcd/clever-system-tft.html) TFT Displays.

#### Features

The library features HW and SW serail support the default baud rate for the M Series is 19200.  

Hardware Serial Support:

```
WFxx WF32M(Serial1);

void setup() {
  Serial1.begin(19200);
}
```

Software Serial Support:

```
SoftwareSerial WFxxSerial(10, 11); //RX, TX

WFxx WF32M(WFxxSerial);

void setup() {
  WFxxSerial.begin(19200);
}
```

To download, click the ZIP button in the top navbar, rename the uncompressed folder Winstar-WFxx. Check that the Adafruit_HDC1000 folder contains Winstar-WFxx.cpp and Winstar-WFxx.h

Place the Winstar-WFxx library folder your arduinosketchfolder/libraries/ folder. You may need to create the libraries subfolder if its your first library. Restart the IDE.

#### Compatibility

| MCU Tested         | Works         | Doesn't Work  | Not Tested    | Notes         |
| -------------      | ------------- | ------------- | ------------- | ------------- |
| Atmega328 @ 16MHz  | X             |               |               |               |
| Atmega32u4 @ 16MHz | X             |               |               |               |
| ESP8266            | X             |               |               |               |
| Atmega2560         | X             |               |               |               |
| ATSAM3X8E          | X             |               |               |               |
| ATSAM21D           | X             |               |               |               |

- ATmega328 @ 16MHz : Arduino UNO
- ATmega32u4 @ 16MHz : Arduino Leonardo, Arduino Micro, Arduino Yun
- ESP8266 : ...
- ATmega2560 @ 16MHz : Arduino Mega
- ATSAM3X8E : Arduino Due
- ATSAM21D : Arduino Zero, M0 Pro

#### Demo

to do 

#### To Do

to do 