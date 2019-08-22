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

#include <Arduino.h>

#define   SB1               0x01
#define   SB2               0x02
#define   SB3               0x04

#define   EB1               0x0A
#define   EB2               0x0D

#define   Staring           0x31
#define   Graphic           0x32
#define   Pixel             0x33  
#define   Line              0x34
#define   Square            0x35
#define   Clear             0x36
#define   PWM               0x37
#define   SET_BL            0x39   
#define   CAL_RTP           0x7E    

#define   Graphic_Length    0x0F
#define   Line_Length       0x15
#define   Pixel_Length      0x10
#define   Square_Length     0x15
#define   Staring_Length    0x14
#define   PWM_Length        0x0D
#define   Clear_Length      0x10
#define   SET_BL_Length     0x0A    
#define   CAL_RTP_Length    0x08    

#define   ACK               0x06
#define   NAK               0x15
#define   RTP               0x41

#define   SW_PRESSED        0x40    
#define   SW1               0x41
#define   SW2               0x42
#define   SW3               0x43
#define   SW4               0x44   
#define   SW_RELEASED       0x20

class WFxx
{
public:

  WFxx(Stream& serial);

  void Picture_Command(char Display_Level,char Rotation,int X_Point,int Y_Point,int Picture_Number);
  void Text_Command(char Font_Type,char Display_Level,char Transparent,char Rotation,int X_Point,int Y_Point,unsigned long String_Color,unsigned long Back_Color,unsigned char String_Data[]);
  void Paint_Square_Command(char Display_Level,char Rotation,int X_Start,int Y_Start,int X_End,int Y_End,int Pixel_,unsigned long Color);
  void Paint_Line_Command(char Display_Level,char Rotation,int X_Start,int Y_Start,int X_End,int Y_End,int Pixel_,unsigned long Color);
  void Pixel_Command(char Display_Level,char Rotation,int X_Point,int Y_Point,unsigned long Pixel_Color);

  void Clear_Command(int X_Point,int Y_Point,int X_End,int Y_End);

  void PWM_Frequency_Command(char PWM_Select,char PWM_ON_OFF,int PWM_Freq,int PWM_Duty_Cycle);
  void Buzzer_Command(void);

  void Set_Backlight_Command(int BL_Value);
  void Calibrate_TP_Command(void);

  unsigned char BCC_Calculate(unsigned char *String);
  uint8_t Check_WFxx_Feedback();
  
  uint8_t TP();
	uint16_t X_Touch, Y_Touch;

private:
  Stream& WFxxM; 
  char feedbackBuffer[5];

};