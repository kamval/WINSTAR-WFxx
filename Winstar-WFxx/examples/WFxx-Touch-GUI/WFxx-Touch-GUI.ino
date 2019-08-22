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
// for use with Hardware Serial

#include <Winstar-WFxx.h>

WFxx WF32M(Serial);

int ledState = 0;             
unsigned long previousTime = 0;        
const long interval = 500;  

int screen = 0;
unsigned long WFxxTimeout = 0; 

void setup() {

  Serial.begin(19200);
  delay(50);
  Load_Welcome_Screen();
  delay(50);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(50);
}

void loop() {

  unsigned long currentTime = millis();

  if (currentTime - previousTime >= interval) {
    previousTime = currentTime;
    if (ledState == 0) {
      ledState = 1;
    } else {
      ledState = 0;
    }
    digitalWrite(LED_BUILTIN, ledState);
    WFxxTimeout++;
  }

  if (WFxxTimeout >= 10 && screen > 0){
      Load_Welcome_Screen();
      WFxxTimeout = 0;
      screen = 0; 
  } else if(WFxxTimeout >= 10 && screen == 0){
      Set_Screen_Backlight();
      WFxxTimeout = 0;
  }    
      
  if(WF32M.TP() == 1) {
      
      WFxxTimeout = 0; 

      if (screen == 0){
        Welcome_Screen_Process(); 
      }
      
      if(screen == 1){
        Tiles_Screen_Process(); 
      }

      if(screen == 2){
        Heating_Screen_Process(); 
      }  

      if(screen == 3){
        Lighting_Screen_Process(); 
      }  

      if(screen == 4){
        Environment_Screen_Process(); 
      }  
      if(screen == 5){
        Energy_Screen_Process(); 
      }  
  }
}

void Load_Welcome_Screen(void){
    WF32M.Picture_Command(3,0,0,0,0);
    WF32M.Text_Command(0,3,0,0,80,180,0xFFFFFF,0xFFFFFF,"Welcome");
}

void Set_Screen_Backlight(void){
    // add lux sensor
    WF32M.Set_Backlight_Command(30);  
}

void Welcome_Screen_Process(void){
    
    if(WF32M.X_Touch > 0 && WF32M.X_Touch < 320 && WF32M.Y_Touch > 0 && WF32M.Y_Touch < 240 ){
        WF32M.Picture_Command(3,0,0,0,1);

        WF32M.X_Touch = 0; 
        WF32M.Y_Touch = 0;

        screen = 1; // go to Tiles_Screen_Process()
    }
}

void Tiles_Screen_Process(void){

   if(WF32M.X_Touch > 0 && WF32M.X_Touch < 160 && WF32M.Y_Touch > 0 && WF32M.Y_Touch < 120 )
    {
      WF32M.Picture_Command(3,0,0,0,2);
      WF32M.Picture_Command(3,0,282,197,7);

      // demo data
      WF32M.Text_Command(0,3,0,0,20,130,0xC4DC90,0xC4DC90,"Kitchen");
      WF32M.Text_Command(0,3,0,0,200,130,0x84B818,0xC4DC90,"OFF");

      WF32M.Text_Command(0,3,0,0,20,180,0xC4DC90,0xC4DC90,"Bedroom");
      WF32M.Text_Command(0,3,0,0,200,180,0x84B818,0xC4DC90,"OFF");

      WF32M.X_Touch = 0; 
      WF32M.Y_Touch = 0;

      screen = 2;   // go to Heating_Screen_Process()
    }

    if(WF32M.X_Touch > 160 && WF32M.X_Touch < 320 && WF32M.Y_Touch > 0 && WF32M.Y_Touch < 120 )
    {
          
      WF32M.Picture_Command(3,0,0,0,3);
      WF32M.Picture_Command(3,0,282,197,7);
      
      // demo data
      WF32M.Text_Command(0,3,0,0,20,130,0xC4DC90,0xC4DC90,"Bathroom");
      WF32M.Text_Command(0,3,0,0,200,130,0x84B818,0xC4DC90,"OFF");

      WF32M.Text_Command(0,3,0,0,20,180,0xC4DC90,0xC4DC90,"Bedroom");
      WF32M.Text_Command(0,3,0,0,200,180,0x84B818,0xC4DC90,"ON");

      WF32M.X_Touch = 0; 
      WF32M.Y_Touch = 0;

      screen = 3;   // go to Lighting_Screen_Process()
    }

    if(WF32M.X_Touch > 0 && WF32M.X_Touch < 160 && WF32M.Y_Touch > 120 && WF32M.Y_Touch < 240 )
    {

      WF32M.Picture_Command(3,0,0,0,4);
      WF32M.Picture_Command(3,0,282,197,7);

      // demo data
      WF32M.Text_Command(0,3,0,0,20,130,0xC4DC90,0xC4DC90,"Temp");
      WF32M.Text_Command(0,3,0,0,135,130,0x84B818,0x84B818,"24");
      WF32M.Text_Command(0,3,0,0,190,130,0xC4DC90,0xC4DC90,"C");

      WF32M.Text_Command(0,3,0,0,20,180,0xC4DC90,0xC4DC90,"Hum");
      WF32M.Text_Command(0,3,0,0,135,180,0x84B818,0x84B818,"30");
      WF32M.Text_Command(0,3,0,0,190,180,0xC4DC90,0xC4DC90,"%");
      
      WF32M.X_Touch = 0; 
      WF32M.Y_Touch = 0;

      screen = 4;   // go to Environment_Screen_Process()
    }

    if(WF32M.X_Touch > 160 && WF32M.X_Touch < 320 && WF32M.Y_Touch > 120 && WF32M.Y_Touch < 240 )
    {
      WF32M.Picture_Command(3,0,0,0,5);
      WF32M.Picture_Command(3,0,282,197,7);

      // demo data
      WF32M.Text_Command(0,3,0,0,20,130,0xC4DC90,0xC4DC90,"Curr");
      WF32M.Text_Command(0,3,0,0,110,130,0x84B818,0x84B818,"20");
      WF32M.Text_Command(0,3,0,0,190,130,0xC4DC90,0xC4DC90,"A");

      WF32M.Text_Command(0,3,0,0,20,180,0xC4DC90,0xC4DC90,"Volt");
      WF32M.Text_Command(0,3,0,0,110,180,0x84B818,0x84B818,"230");
      WF32M.Text_Command(0,3,0,0,190,180,0xC4DC90,0xC4DC90,"VAC");

      WF32M.X_Touch = 0; 
      WF32M.Y_Touch = 0;

      screen = 5;   // go to Energy_Screen_Process()
    }
}     

void Heating_Screen_Process(void){

     if(WF32M.X_Touch > 282 && WF32M.X_Touch < 320 && WF32M.Y_Touch > 197 && WF32M.Y_Touch < 240 )
    {
      WF32M.Picture_Command(3,0,282,197,6);
      WF32M.Picture_Command(3,0,0,0,1);
      
      WF32M.X_Touch = 0; 
      WF32M.Y_Touch = 0;

      screen = 1;   // go to back Tiles_Screen_Process()
    }
}    

void Lighting_Screen_Process(void){

     if(WF32M.X_Touch > 282 && WF32M.X_Touch < 320 && WF32M.Y_Touch > 197 && WF32M.Y_Touch < 240 )
    {
      WF32M.Picture_Command(3,0,282,197,6);
      WF32M.Picture_Command(3,0,0,0,1);
      
      WF32M.X_Touch = 0; 
      WF32M.Y_Touch = 0;

      screen = 1;   // go to back Tiles_Screen_Process()
    }
}    

void Environment_Screen_Process(void){

     if(WF32M.X_Touch > 282 && WF32M.X_Touch < 320 && WF32M.Y_Touch > 197 && WF32M.Y_Touch < 240 )
    {
      WF32M.Picture_Command(3,0,282,197,6);
      WF32M.Picture_Command(3,0,0,0,1);
      
      WF32M.X_Touch = 0; 
      WF32M.Y_Touch = 0;

      screen = 1;   // go to back Tiles_Screen_Process()
    }
}    

void Energy_Screen_Process(void){

     if(WF32M.X_Touch > 282 && WF32M.X_Touch < 320 && WF32M.Y_Touch > 197 && WF32M.Y_Touch < 240 )
    {
      WF32M.Picture_Command(3,0,282,197,6);
      WF32M.Picture_Command(3,0,0,0,1);
      
      WF32M.X_Touch = 0; 
      WF32M.Y_Touch = 0;

      screen = 1;   // go to back Tiles_Screen_Process()
    }
}    