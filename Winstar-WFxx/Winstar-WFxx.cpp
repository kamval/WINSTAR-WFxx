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

#include <Winstar-WFxx.h>

WFxx::WFxx(Stream& serial):WFxxM(serial) 
{ 

}

//*******************************************************************************************************************
//  Picture_Command
//*******************************************************************************************************************
//
//Display_Level   -->   Display Layer Control (Function)      Variables Range: 0x00 ~ 0x03
//                      Level 1 Paint       -->   0x00
//                      Copy to Base        -->   0x01
//                      Erase               -->   0x02
//                      Display Level 1     -->   0x03
//
//*******************************************************************************************************************
//
//Rotation        -->   Flip Screen (Rotation)                Variables Range: 0x00 ~ 0x01
//                -->   0 (Do not Flip)     -->   0x00
//                -->   180(Flip)           -->   0x01
//
//*******************************************************************************************************************
//
//X_Point         --> Image Coordinates: X Position(X Axis)   Variables Range: 0 ~ 320(WF35M), 0 ~ 480(WF43M) 
//  
//*******************************************************************************************************************
//
//Y_Point         --> Image Coordinates: Y Position(Y Axis)   Variables Range: 0 ~ 240(WF35M), 0 ~ 272(WF43M)
//
//*******************************************************************************************************************
//
//Picture_Number  --> Number of the Preloaded Image           Variables Range: 0 ~ 1024
//  
//*******************************************************************************************************************
//*******************************************************************************************************************

void WFxx::Picture_Command(char Display_Level,char Rotation,int X_Point,int Y_Point,int Picture_Number)
{
  unsigned char WFxx_Command_Buffer[Graphic_Length];

  WFxx_Command_Buffer[0] = SB1;
  WFxx_Command_Buffer[1] = Graphic_Length;
  WFxx_Command_Buffer[2] = SB2;
  WFxx_Command_Buffer[3] = SB3;
  WFxx_Command_Buffer[4] = Graphic;
  WFxx_Command_Buffer[5] = ((Display_Level << 4) & 0xF0) + Rotation;
  WFxx_Command_Buffer[6] = (X_Point >> 8);
  WFxx_Command_Buffer[7] = X_Point;
  WFxx_Command_Buffer[8] = (Y_Point >> 8);
  WFxx_Command_Buffer[9] = Y_Point;
  WFxx_Command_Buffer[10]= (Picture_Number >> 8);
  WFxx_Command_Buffer[11]= Picture_Number;
  WFxx_Command_Buffer[12]= EB1;
  WFxx_Command_Buffer[13]= BCC_Calculate(WFxx_Command_Buffer);
  WFxx_Command_Buffer[14]= EB2;
  
  WFxxM.write(WFxx_Command_Buffer, sizeof(WFxx_Command_Buffer));
 
  while(Check_WFxx_Feedback()!=ACK);
}

//*******************************************************************************************************************
//  Text_Command
//*******************************************************************************************************************
//
//Font_Type       --> Select built-in Font Library (Font)     Variables Range: 0x00 ~ 0x0F
//        
//*******************************************************************************************************************
//
//Display_Level   -->   Display Layer Control (Function)      Variables Range: 0x00 ~ 0x03
//                      Level 1 Paint       -->   0x00
//                      Copy to Base        -->   0x01
//                      Erase               -->   0x02
//                      Display Level 1     -->   0x03
//
//*******************************************************************************************************************
//
//Transparent     --> Text Background (Background)            Variables Range: 0x00 ~ 0x01
//                    Do not Display Text Background    -->   0x00
//                    Display Text Background           -->   0x01
//
//*******************************************************************************************************************
//
//Rotation        -->   Flip Screen (Rotation)                Variables Range: 0x00 ~ 0x01
//                -->   0 (Do not Flip)     -->   0x00
//                -->   180(Flip)           -->   0x01
//
//*******************************************************************************************************************
//
//X_Point         --> Text Coordinates: X Position(X Axis)    Variables Range: 0 ~ 320(WF35M), 0 ~ 480(WF43M) 
//  
//*******************************************************************************************************************
//
//Y_Point         --> Text Coordinates: Y Position(Y Axis)    Variables Range: 0 ~ 240(WF35M), 0 ~ 272(WF43M)
//
//*******************************************************************************************************************
//
//String_Color    --> Text Color                              Variables Range: (R:G:B) 0x000000 ~ 0xFFFFFF
//                    R = 0x00 ~ 0xFF:G = 0x00 ~ 0xFF:B = 0x00 ~ 0xFF
//                                  
//*******************************************************************************************************************
//
//Back_Color      --> Text Background Color                   Variables Range: (R:G:B) 0x000000 ~ 0xFFFFFF
//                    R = 0x00 ~ 0xFF:G = 0x00 ~ 0xFF:B = 0x00 ~ 0xFF
//                                  
//*******************************************************************************************************************
//
//String_Data[]   -->  Text String to be Displayed            "String"
//
//*******************************************************************************************************************
//
//Example 1:  Text_Command(0,3,1,0,0,0,0xFFFFFF,0x000000,"Hello world");
//            Display Coordinates(0,0), White on Black (0xFFFFFF,0x000000), String ("Hello world")
//
//Example 2:  Text_Command(0,3,0,0,0,0,0xFFFFFF,0x000000,"Hello world");
//            Display Coordinates(0,0), White Text (0xFFFFFF,0x000000), String ("Hello world")
//
//*******************************************************************************************************************
//*******************************************************************************************************************

void WFxx::Text_Command(char Font_Type,char Display_Level,char Transparent,char Rotation,int X_Point,int Y_Point,unsigned long String_Color,unsigned long Back_Color,unsigned char String_Data[])
{
  uint8_t Word_Lengh = 0;
  unsigned char WFxx_Command_Buffer[30];

  while(String_Data[Word_Lengh] != '\0')
  {
    WFxx_Command_Buffer[17 + Word_Lengh] = String_Data[Word_Lengh];
    Word_Lengh++;
  }
  
  WFxx_Command_Buffer[0] = SB1;
  WFxx_Command_Buffer[1] = Word_Lengh + Staring_Length;
  WFxx_Command_Buffer[2] = SB2;
  WFxx_Command_Buffer[3] = SB3;
  WFxx_Command_Buffer[4] = Staring;
  WFxx_Command_Buffer[5] = ((Font_Type << 4) & 0xF0) + Display_Level;
  WFxx_Command_Buffer[6] = ((Transparent << 4) & 0xF0) + Rotation;
  WFxx_Command_Buffer[7] = (X_Point >> 8);
  WFxx_Command_Buffer[8] = X_Point;
  WFxx_Command_Buffer[9] = (Y_Point >> 8);
  WFxx_Command_Buffer[10] = Y_Point;
  WFxx_Command_Buffer[11]= (String_Color >> 16);
  WFxx_Command_Buffer[12]= (String_Color >> 8);
  WFxx_Command_Buffer[13]= String_Color;
  WFxx_Command_Buffer[14]= (Back_Color >> 16);
  WFxx_Command_Buffer[15]= (Back_Color >> 8);
  WFxx_Command_Buffer[16]=  Back_Color;

  WFxx_Command_Buffer[(Word_Lengh + Staring_Length) - 3] = EB1;
  WFxx_Command_Buffer[(Word_Lengh + Staring_Length) - 2] = BCC_Calculate(WFxx_Command_Buffer);
  WFxx_Command_Buffer[(Word_Lengh + Staring_Length) - 1] = EB2;
  
  WFxxM.write(WFxx_Command_Buffer, sizeof(WFxx_Command_Buffer));
 
  while(Check_WFxx_Feedback()!=ACK);
}

//*******************************************************************************************************************
//  Paint_Square_Command
//*******************************************************************************************************************
//
//Display_Level   -->   Display Layer Control (Function)             Variables Range: 0x00 ~ 0x03
//                      Level 1 Paint       -->   0x00
//                      Copy to Base        -->   0x01
//                      Erase               -->   0x02
//                      Display Level 1     -->   0x03
//
//*******************************************************************************************************************
//
//Rotation        -->   Flip Screen (Rotation)                       Variables Range: 0x00 ~ 0x01
//                -->   0 (Do not Flip)     -->   0x00
//                -->   180(Flip)           -->   0x01
//
//*******************************************************************************************************************
//
//X_Start         --> Square Coordinates: Start X Position(X Axis)   Variables Range: 0 ~ 320(WF35M, 0 ~ 480(WF43M)   
//
//*******************************************************************************************************************
//
//Y_Start         --> Square Coordinates: Start Y Position(Y Axis)   Variables Range: 0 ~ 240(WF35M), 0 ~ 272(WF43M)
//
//*******************************************************************************************************************
//
//X_End           --> Square Coordinates: End X Position(X Axis)     Variables Range: 0 ~ 320(WF35M), 0 ~ 480(WF43M)
//  
//*******************************************************************************************************************
//
//Y_End           --> Square Coordinates: End Y Position(X Axis)     Variables Range: 0 ~ 240(WF35M), 0 ~ 272(WF43M)
//
//*******************************************************************************************************************
//
//Pixel_          --> Line Thickness (Dot Size)                      Variables range: 0 ~ 5
//
//*******************************************************************************************************************
//
//Color           --> Square Color (Color)                           Variables range: (R:G:B) 0x000000 ~ 0xFFFFFF
//                    R = 0x00 ~ 0xFF:G = 0x00 ~ 0xFF:B = 0x00 ~ 0xFF
//
//*******************************************************************************************************************
//*******************************************************************************************************************

void WFxx::Paint_Square_Command(char Display_Level,char Rotation,int X_Start,int Y_Start,int X_End,int Y_End,int Pixel_,unsigned long Color)
{
  unsigned char WFxx_Command_Buffer[Square_Length];
  
  WFxx_Command_Buffer[0] = SB1;
  WFxx_Command_Buffer[1] = Square_Length;
  WFxx_Command_Buffer[2] = SB2;
  WFxx_Command_Buffer[3] = SB3;
  WFxx_Command_Buffer[4] = Square;
  WFxx_Command_Buffer[5] = ((Display_Level << 4) & 0xF0) + Rotation;
  WFxx_Command_Buffer[6] = (X_Start >> 8);
  WFxx_Command_Buffer[7] = X_Start;
  WFxx_Command_Buffer[8] = (Y_Start >> 8);
  WFxx_Command_Buffer[9] = Y_Start;

  WFxx_Command_Buffer[10] = (X_End >> 8);
  WFxx_Command_Buffer[11] = X_End;
  WFxx_Command_Buffer[12] = (Y_End >> 8);
  WFxx_Command_Buffer[13] = Y_End;
  WFxx_Command_Buffer[14] = Pixel_;

  WFxx_Command_Buffer[15]= (Color >> 16);
  WFxx_Command_Buffer[16]= (Color >> 8);
  WFxx_Command_Buffer[17]= Color;

  WFxx_Command_Buffer[18]= EB1;
  WFxx_Command_Buffer[19]= BCC_Calculate(WFxx_Command_Buffer);
  WFxx_Command_Buffer[20]= EB2;

  WFxxM.write(WFxx_Command_Buffer, sizeof(WFxx_Command_Buffer));
 
  while(Check_WFxx_Feedback()!=ACK);
}

//*******************************************************************************************************************
//  Paint_Line_Command
//*******************************************************************************************************************
//
//Display_Level   -->   Display Layer Control (Function)         Variables Range: 0x00 ~ 0x03
//                      Level 1 Paint       -->   0x00
//                      Copy to Base        -->   0x01
//                      Erase               -->   0x02
//                      Display Level 1     -->   0x03
//
//*******************************************************************************************************************
//
//Rotation        -->   Flip Screen (Rotation)                    Variables Range: 0x00 ~ 0x01
//                -->   0 (Do not Flip)     -->   0x00
//                -->   180(Flip)           -->   0x01
//
//*******************************************************************************************************************
//
//X_Start       --> Line Coordinates: Start X Position(X Axis)    Variables Range: 0 ~ 320(WF35M)、0 ~ 480(WF43M)   
//
//*******************************************************************************************************************
//
//Y_Start       --> Line Coordinates: Start Y Position(Y Axis)    Variables Range: 0 ~ 240(WF35M)、0 ~ 272(WF43M)
//
//*******************************************************************************************************************
//
//X_End         --> Line Coordinates: End X Position(X Axis)      Variables Range: 0 ~ 320(WF35M)、0 ~ 480(WF43M)
//  
//*******************************************************************************************************************
//
//Y_End         --> Line Coordinates: End Y Position(X Axis)      Variables Range: 0 ~ 240(WF35M)、0 ~ 272(WF43M)
//
//*******************************************************************************************************************
//
//Pixel_        --> Line Thickness (Dot Size)                     Variables range: 0 ~ 5
//
//*******************************************************************************************************************
//
//Color         --> Line Color (Color)                            Variables range: (R:G:B) 0x000000 ~ 0xFFFFFF
//                  R = 0x00 ~ 0xFF:G = 0x00 ~ 0xFF:B = 0x00 ~ 0xFF
//
//*******************************************************************************************************************
//*******************************************************************************************************************

void WFxx::Paint_Line_Command(char Display_Level,char Rotation,int X_Start,int Y_Start,int X_End,int Y_End,int Pixel_,unsigned long Color)
{
  unsigned char WFxx_Command_Buffer[Square_Length];
  
  WFxx_Command_Buffer[0] = SB1;
  WFxx_Command_Buffer[1] = Line_Length;
  WFxx_Command_Buffer[2] = SB2;
  WFxx_Command_Buffer[3] = SB3;
  WFxx_Command_Buffer[4] = Line;
  WFxx_Command_Buffer[5] = ((Display_Level << 4) & 0xF0) + Rotation;
  WFxx_Command_Buffer[6] = (X_Start >> 8);
  WFxx_Command_Buffer[7] = X_Start;
  WFxx_Command_Buffer[8] = (Y_Start >> 8);
  WFxx_Command_Buffer[9] = Y_Start;

  WFxx_Command_Buffer[10] = (X_End >> 8);
  WFxx_Command_Buffer[11] = X_End;
  WFxx_Command_Buffer[12] = (Y_End >> 8);
  WFxx_Command_Buffer[13] = Y_End;
  WFxx_Command_Buffer[14] = Pixel_;

  WFxx_Command_Buffer[15]= (Color >> 16);
  WFxx_Command_Buffer[16]= (Color >> 8);
  WFxx_Command_Buffer[17]= Color;

  WFxx_Command_Buffer[18]= EB1;
  WFxx_Command_Buffer[19]= BCC_Calculate(WFxx_Command_Buffer);
  WFxx_Command_Buffer[20]= EB2;
  
  WFxxM.write(WFxx_Command_Buffer, sizeof(WFxx_Command_Buffer));
 
  while(Check_WFxx_Feedback()!=ACK);
}

//*******************************************************************************************************************
//  Pixel_Command
//*******************************************************************************************************************
//
//Display_Level   -->   Display Layer Control (Function)              Variables Range: 0x00 ~ 0x03
//                      Level 1 Paint       -->   0x00
//                      Copy to Base        -->   0x01
//                      Erase               -->   0x02
//                      Display Level 1     -->   0x03
//
//*******************************************************************************************************************
//
//Rotation        -->   Flip Screen (Rotation)                        Variables Range: 0x00 ~ 0x01
//                -->   0 (Do not Flip)     -->   0x00
//                -->   180(Flip)           -->   0x01
//
//*******************************************************************************************************************
//
//X_Point         --> Text Coordinates: X Position(X Axis)            Variables Range: 0 ~ 320(WF35M), 0 ~ 480(WF43M) 
//  
//*******************************************************************************************************************
//
//Y_Point         --> Text Coordinates: Y Position(Y Axis)            Variables Range: 0 ~ 240(WF35M), 0 ~ 272(WF43M)
//
//*******************************************************************************************************************
//
//Color           --> Square Color (Color)                            Variables range: (R:G:B) 0x000000 ~ 0xFFFFFF
//                    R = 0x00 ~ 0xFF:G = 0x00 ~ 0xFF:B = 0x00 ~ 0xFF
//
//*******************************************************************************************************************
//*******************************************************************************************************************

void WFxx::Pixel_Command(char Display_Level,char Rotation,int X_Point,int Y_Point,unsigned long Pixel_Color)
{
  unsigned char WFxx_Command_Buffer[Pixel_Length];

  WFxx_Command_Buffer[0] = SB1;
  WFxx_Command_Buffer[1] = Pixel_Length;
  WFxx_Command_Buffer[2] = SB2;
  WFxx_Command_Buffer[3] = SB3;
  WFxx_Command_Buffer[4] = Pixel;
  WFxx_Command_Buffer[5] = ((Display_Level << 4) & 0xF0) + Rotation;
  WFxx_Command_Buffer[6] = (X_Point >> 8);
  WFxx_Command_Buffer[7] = X_Point;
  WFxx_Command_Buffer[8] = (Y_Point >> 8);
  WFxx_Command_Buffer[9] = Y_Point;
  WFxx_Command_Buffer[10]= (Pixel_Color >> 16);
  WFxx_Command_Buffer[11]= (Pixel_Color >> 8);
  WFxx_Command_Buffer[12]=  Pixel_Color;
  WFxx_Command_Buffer[13]= EB1;
  WFxx_Command_Buffer[14]= BCC_Calculate(WFxx_Command_Buffer);
  WFxx_Command_Buffer[15]= EB2;
  
  WFxxM.write(WFxx_Command_Buffer, sizeof(WFxx_Command_Buffer));
 
  while(Check_WFxx_Feedback()!=ACK);
}

//*******************************************************************************************************************
//  Clear_Command
//*******************************************************************************************************************
//
//X_Point       --> Clear Coordinates: Start X Position(X Axis)   Variables Range: 0 ~ 320(WF35M), 0 ~ 480(WF43M)     
//
//*******************************************************************************************************************
//
//Y_Point       --> Clear Coordinates: Start Y Position(Y Axis)   Variables Range: 0 ~ 240(WF35M), 0 ~ 272(WF43M)
//
//*******************************************************************************************************************
//
//X_End         --> Clear Coordinates: End X Position(X Axis)     Variables Range: 0 ~ 320(WF35M), 0 ~ 480(WF43M) 
//  
//*******************************************************************************************************************
//
//Y_End         --> Clear Coordinates: End Y Position(X Axis)     Variables Range: 0 ~ 240(WF35M), 0 ~ 272(WF43M)
//
//*******************************************************************************************************************
//
//Erase_Level   --> Layer Control                                 Variables range: 0x36, 0x41
//                  Erase               -->   0x41
//                  Display Level 1     -->   0x36  
//  
//*******************************************************************************************************************
//*******************************************************************************************************************

void WFxx::Clear_Command(int X_Point,int Y_Point,int X_End,int Y_End)
{
  unsigned char WFxx_Command_Buffer[Graphic_Length];

  WFxx_Command_Buffer[0] = SB1;
  WFxx_Command_Buffer[1] = Clear_Length;
  WFxx_Command_Buffer[2] = SB2;
  WFxx_Command_Buffer[3] = SB3;
  WFxx_Command_Buffer[4] = Clear;
  WFxx_Command_Buffer[5] = (X_Point >> 8);
  WFxx_Command_Buffer[6] = X_Point;
  WFxx_Command_Buffer[7] = (Y_Point >> 8);
  WFxx_Command_Buffer[8] = Y_Point;
  WFxx_Command_Buffer[9] = (X_End >> 8);
  WFxx_Command_Buffer[10] = X_End;
  WFxx_Command_Buffer[11] = (Y_End >> 8);
  WFxx_Command_Buffer[12] = Y_End;
  WFxx_Command_Buffer[13]= EB1;
  WFxx_Command_Buffer[14]= BCC_Calculate(WFxx_Command_Buffer);
  WFxx_Command_Buffer[15]= EB2;
  
  WFxxM.write(WFxx_Command_Buffer, sizeof(WFxx_Command_Buffer));
 
  while(Check_WFxx_Feedback()!=ACK);
}

void WFxx::PWM_Frequency_Command(char PWM_Select,char PWM_ON_OFF,int PWM_Freq,int PWM_Duty_Cycle)
{
  unsigned char WFxx_Command_Buffer[PWM_Length];
  
  WFxx_Command_Buffer[0] = SB1;
  WFxx_Command_Buffer[1] = PWM_Length;
  WFxx_Command_Buffer[2] = SB2;
  WFxx_Command_Buffer[3] = SB3;
  WFxx_Command_Buffer[4] = PWM;
  WFxx_Command_Buffer[5] = ((PWM_Select << 4) & 0xF0) + PWM_ON_OFF;
  WFxx_Command_Buffer[6] = (PWM_Freq >> 8);
  WFxx_Command_Buffer[7] = PWM_Freq;
  WFxx_Command_Buffer[8] = (PWM_Duty_Cycle >> 8);
  WFxx_Command_Buffer[9] = PWM_Duty_Cycle;
  WFxx_Command_Buffer[10]= EB1;
  WFxx_Command_Buffer[11]= BCC_Calculate(WFxx_Command_Buffer);
  WFxx_Command_Buffer[12]= EB2;

  WFxxM.write(WFxx_Command_Buffer, sizeof(WFxx_Command_Buffer));
 
  while(Check_WFxx_Feedback()!=ACK);
}

void WFxx::Buzzer_Command(void)
{
  int i = 0;
  
  PWM_Frequency_Command(1,1,100,100);
  while(i++ < 100);
  PWM_Frequency_Command(1,1,0,0);
}

void WFxx::Set_Backlight_Command(int BL_Value)
{
  unsigned char WFxx_Command_Buffer[SET_BL_Length];
  
  WFxx_Command_Buffer[0] = SB1;
  WFxx_Command_Buffer[1] = SET_BL_Length;
  WFxx_Command_Buffer[2] = SB2;
  WFxx_Command_Buffer[3] = SB3;
  WFxx_Command_Buffer[4] = SET_BL;
  WFxx_Command_Buffer[5] = (BL_Value >> 8);
  WFxx_Command_Buffer[6] = BL_Value;
  WFxx_Command_Buffer[7]= EB1;
  WFxx_Command_Buffer[8]= BCC_Calculate(WFxx_Command_Buffer);
  WFxx_Command_Buffer[9]= EB2;
  
  WFxxM.write(WFxx_Command_Buffer, sizeof(WFxx_Command_Buffer));
 
  while(Check_WFxx_Feedback()!=ACK);
}

void WFxx::Calibrate_TP_Command(void)
{
	unsigned char WFxx_Command_Buffer[CAL_RTP_Length];
	WFxx_Command_Buffer[0] = SB1;
	WFxx_Command_Buffer[1] = CAL_RTP_Length;
	WFxx_Command_Buffer[2] = SB2;
	WFxx_Command_Buffer[3] = SB3;
	WFxx_Command_Buffer[4] = CAL_RTP;
	WFxx_Command_Buffer[5]= EB1;
	WFxx_Command_Buffer[6]= BCC_Calculate(WFxx_Command_Buffer);
	WFxx_Command_Buffer[7]= EB2;

  WFxxM.write(WFxx_Command_Buffer, sizeof(WFxx_Command_Buffer));
 
  while(Check_WFxx_Feedback()!=ACK);
}

unsigned char WFxx::BCC_Calculate(unsigned char *String)
{
  unsigned char BCC = 0;
  int i,Command_Length = String[1];

  for(i = 0;i < Command_Length - 2;i++)
  {
    BCC = String[i] + BCC;
  }
  
  return BCC; 
}

uint8_t WFxx::Check_WFxx_Feedback()
{
  uint16_t timeout = 318;     //318*15.72=5000us = 5ms

	while(!WFxxM.available())   //one loop is about 15.72us
	{
		timeout--;
		if(!timeout) return 0;
	}  
  
  for (uint8_t i=0; i<5; i++)
  {
    feedbackBuffer[i] = WFxxM.read();
    delay(2);
  } 

  switch (feedbackBuffer[0])
  {
    case ACK:
      return ACK;
      break;
    case NAK:
      return NAK;
      break;
    case RTP:
      return RTP;
      break; 
    default:
      return feedbackBuffer[0];
      break;
  }
}

uint8_t WFxx::TP()
{
	if(Check_WFxx_Feedback() == RTP)
	{ 
		X_Touch = ((uint8_t)feedbackBuffer[1] * 0x100) + (uint8_t)feedbackBuffer[2];
		Y_Touch = ((uint8_t)feedbackBuffer[3] * 0x100) + (uint8_t)feedbackBuffer[4];

		return 1;
	}
	else return 0;
}