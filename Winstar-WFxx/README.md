### Winstar Clever System Arduino Library

Simple arduino library, showing the main capabilities of Winstar [M Series](https://www.winstar.com.tw/products/tft-lcd/clever-system-tft.html) TFT Displays.

#### Features

The library features HW and SW serial support, the default baud rate for the M Series is 19200.  

Hardware serial support example:

```
WFxx WF32M(Serial1);

void setup() {
  Serial1.begin(19200);
  ...
}
...
```

Software serial support example: 

```
SoftwareSerial WFxxSerial(10, 11);

WFxx WF32M(WFxxSerial);

void setup() {
  WFxxSerial.begin(19200);
  ...
}
...

```

To download this library, click the ZIP button in the top navbar, rename the uncompressed folder Winstar-WFxx. Check that the Winstar-WFxx folder contains Winstar-WFxx.cpp and Winstar-WFxx.h

Place the Winstar-WFxx library folder your arduinosketchfolder/libraries/ folder. You may need to create the libraries subfolder if its your first library. Restart the IDE.

#### Compatibility

| MCU Tested         | Works         | Doesn't Work  | Not Tested    | Notes         |
| ------------------ | ------------- | ------------- | ------------- | ------------- |
| Atmega328 @ 16MHz  | X             |               |               |               |
| Atmega32u4 @ 16MHz | X             |               | X             |               |
| ESP8266            |               |               | X             |               |
| ESP32              |               |               |               |               |
| Atmega2560         | X             |               |               |               |
| ATSAM3X8E          | X             |               |               |               |
| ATSAM21D           | X             |               |               |               |

- ATmega328 @ 16MHz : Arduino UNO, Arduino Nano
- ATmega32u4 @ 16MHz : Arduino Leonardo, Arduino Micro 
- ESP8266 : NodeMcu
- ESP32 : ESP32-DEVKITC
- ATmega2560 @ 16MHz : Arduino Mega
- ATSAM3X8E : Arduino Due
- ATSAM21D : Arduino Zero, M0 Pro

#### Demo

Check out the examples

<p align="center">
  <img width="678" height="382" src="https://github.com/kamval/WINSTAR-WFxx/blob/master/WFxx%20Documents/GUI_Demo.gif">
</p>

#### To Do

- Implement SPI support
- Implement hardware SW