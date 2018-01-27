#include <RCSwitch.h>
char incomingByte; 
RCSwitch mySwitch = RCSwitch();
  
//---------------------------------------LCD NOKIA3310
#define PIN_SCE   7
#define PIN_RESET 6
#define PIN_DC    5
#define PIN_SDIN  4
#define PIN_SCLK  8

#define LCD_C     LOW
#define LCD_D     HIGH

#define LCD_X     84
#define LCD_Y     48
//---------------------------------------END LCD NOKIA3310


//------------------------------------CLK

#include <stdio.h>
#include <string.h>
#include <DS1302.h>

/* Set the appropriate digital I/O pin connections */
uint8_t CE_PIN   = 10;
uint8_t IO_PIN   = 11;
uint8_t SCLK_PIN = 12;

/* Create buffers */
char buf[50];
char day[10];

/* Create a DS1302 object */
DS1302 rtc(CE_PIN, IO_PIN, SCLK_PIN);

void print_time()
{
  /* Get the current time and date from the chip */
  Time t = rtc.time();

  /* Name the day of the week */
  memset(day, 0, sizeof(day));  /* clear day buffer */
  switch (t.day) {
    case 1:
      strcpy(day, "SU");
      break;
    case 2:
      strcpy(day, "MO");
      break;
    case 3:
      strcpy(day, "TU");
      break;
    case 4:
      strcpy(day, "WE");
      break;
    case 5:
      strcpy(day, "TH");
      break;
    case 6:
      strcpy(day, "FR");
      break;
    case 7:
      strcpy(day, "SA");
      break;
  }
  /* Format the time and date and insert into the temporary buffer */
  snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d %02d:%02d:%02d",
           day,
           t.yr, t.mon, t.date,
           t.hr, t.min, t.sec);

  /* Print the formatted string to serial so we can see the time */
  Serial.println(buf);
}


//-----------------------------------CLK

int led = 13;
//--------
#include <dht.h>
#define dht_dpin A0 //no ; here. Set equal to channel sensor is on
dht DHT;
//--------

#include <Wire.h> 
#include <BMP085.h>


BMP085 dps = BMP085();    

long Temperature = 0, Pressure = 0, Altitude = 0;


//---------------------------------------LCD NOKIA3310
static const byte ASCII[][5] =
{
 {0x00, 0x00, 0x00, 0x00, 0x00} // 20  
,{0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
,{0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
,{0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
,{0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
,{0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
,{0x36, 0x49, 0x55, 0x22, 0x50} // 26 &
,{0x00, 0x05, 0x03, 0x00, 0x00} // 27 '
,{0x00, 0x1c, 0x22, 0x41, 0x00} // 28 (
,{0x00, 0x41, 0x22, 0x1c, 0x00} // 29 )
,{0x14, 0x08, 0x3e, 0x08, 0x14} // 2a *
,{0x08, 0x08, 0x3e, 0x08, 0x08} // 2b +
,{0x00, 0x50, 0x30, 0x00, 0x00} // 2c ,
,{0x08, 0x08, 0x08, 0x08, 0x08} // 2d -
,{0x00, 0x60, 0x60, 0x00, 0x00} // 2e .
,{0x20, 0x10, 0x08, 0x04, 0x02} // 2f /
,{0x3e, 0x51, 0x49, 0x45, 0x3e} // 30 0
,{0x00, 0x42, 0x7f, 0x40, 0x00} // 31 1
,{0x42, 0x61, 0x51, 0x49, 0x46} // 32 2
,{0x21, 0x41, 0x45, 0x4b, 0x31} // 33 3
,{0x18, 0x14, 0x12, 0x7f, 0x10} // 34 4
,{0x27, 0x45, 0x45, 0x45, 0x39} // 35 5
,{0x3c, 0x4a, 0x49, 0x49, 0x30} // 36 6
,{0x01, 0x71, 0x09, 0x05, 0x03} // 37 7
,{0x36, 0x49, 0x49, 0x49, 0x36} // 38 8
,{0x06, 0x49, 0x49, 0x29, 0x1e} // 39 9
,{0x00, 0x36, 0x36, 0x00, 0x00} // 3a :
,{0x00, 0x56, 0x36, 0x00, 0x00} // 3b ;
,{0x08, 0x14, 0x22, 0x41, 0x00} // 3c <
,{0x14, 0x14, 0x14, 0x14, 0x14} // 3d =
,{0x00, 0x41, 0x22, 0x14, 0x08} // 3e >
,{0x02, 0x01, 0x51, 0x09, 0x06} // 3f ?
,{0x32, 0x49, 0x79, 0x41, 0x3e} // 40 @
,{0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
,{0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
,{0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
,{0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
,{0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
,{0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
,{0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
,{0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
,{0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
,{0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
,{0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
,{0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
,{0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
,{0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
,{0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
,{0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
,{0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
,{0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
,{0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
,{0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
,{0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
,{0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
,{0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
,{0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
,{0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
,{0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
,{0x00, 0x7f, 0x41, 0x41, 0x00} // 5b [
,{0x02, 0x04, 0x08, 0x10, 0x20} // 5c ¥
,{0x00, 0x41, 0x41, 0x7f, 0x00} // 5d ]
,{0x04, 0x02, 0x01, 0x02, 0x04} // 5e ^
,{0x40, 0x40, 0x40, 0x40, 0x40} // 5f _
,{0x00, 0x01, 0x02, 0x04, 0x00} // 60 `
,{0x20, 0x54, 0x54, 0x54, 0x78} // 61 a
,{0x7f, 0x48, 0x44, 0x44, 0x38} // 62 b
,{0x38, 0x44, 0x44, 0x44, 0x20} // 63 c
,{0x38, 0x44, 0x44, 0x48, 0x7f} // 64 d
,{0x38, 0x54, 0x54, 0x54, 0x18} // 65 e
,{0x08, 0x7e, 0x09, 0x01, 0x02} // 66 f
,{0x0c, 0x52, 0x52, 0x52, 0x3e} // 67 g
,{0x7f, 0x08, 0x04, 0x04, 0x78} // 68 h
,{0x00, 0x44, 0x7d, 0x40, 0x00} // 69 i
,{0x20, 0x40, 0x44, 0x3d, 0x00} // 6a j 
,{0x7f, 0x10, 0x28, 0x44, 0x00} // 6b k
,{0x00, 0x41, 0x7f, 0x40, 0x00} // 6c l
,{0x7c, 0x04, 0x18, 0x04, 0x78} // 6d m
,{0x7c, 0x08, 0x04, 0x04, 0x78} // 6e n
,{0x38, 0x44, 0x44, 0x44, 0x38} // 6f o
,{0x7c, 0x14, 0x14, 0x14, 0x08} // 70 p
,{0x08, 0x14, 0x14, 0x18, 0x7c} // 71 q
,{0x7c, 0x08, 0x04, 0x04, 0x08} // 72 r
,{0x48, 0x54, 0x54, 0x54, 0x20} // 73 s
,{0x04, 0x3f, 0x44, 0x40, 0x20} // 74 t
,{0x3c, 0x40, 0x40, 0x20, 0x7c} // 75 u
,{0x1c, 0x20, 0x40, 0x20, 0x1c} // 76 v
,{0x3c, 0x40, 0x30, 0x40, 0x3c} // 77 w
,{0x44, 0x28, 0x10, 0x28, 0x44} // 78 x
,{0x0c, 0x50, 0x50, 0x50, 0x3c} // 79 y
,{0x44, 0x64, 0x54, 0x4c, 0x44} // 7a z
,{0x00, 0x08, 0x36, 0x41, 0x00} // 7b {
,{0x00, 0x00, 0x7f, 0x00, 0x00} // 7c |
,{0x00, 0x41, 0x36, 0x08, 0x00} // 7d }
,{0x10, 0x08, 0x08, 0x10, 0x08} // 7e ←
,{0x78, 0x46, 0x41, 0x46, 0x78} // 7f →
};

void LcdCharacter(const char character)
{
  LcdWrite(LCD_D, 0x00);
  for (int index = 0; index < 5; index++)
  {
    LcdWrite(LCD_D, ASCII[character - 0x20][index]);
  }
  LcdWrite(LCD_D, 0x00);
}

void LcdClear(void)
{
  for (int index = 0; index < LCD_X * LCD_Y / 8; index++)
  {
    LcdWrite(LCD_D, 0x00);
  }
}

void gotoXY(int x, int y)
{
  LcdWrite( 0, 0x80 | x);  // Column.
  LcdWrite( 0, 0x40 | y);  // Row.  

}

void LcdInitialise(void)
{
  pinMode(PIN_SCE, OUTPUT);
  pinMode(PIN_RESET, OUTPUT);
  pinMode(PIN_DC, OUTPUT);
  pinMode(PIN_SDIN, OUTPUT);
  pinMode(PIN_SCLK, OUTPUT);
  digitalWrite(PIN_RESET, LOW);
  digitalWrite(PIN_RESET, HIGH);
  LcdWrite(LCD_C, 0x21 );  // LCD Extended Commands.
  LcdWrite(LCD_C, 0xB1 );  // Set LCD Vop (Contrast). 
  LcdWrite(LCD_C, 0x04 );  // Set Temp coefficent. //0x04
  LcdWrite(LCD_C, 0x14 );  // LCD bias mode 1:48. //0x13
  LcdWrite(LCD_C, 0x0C );  // LCD in normal mode.
  LcdWrite(LCD_C, 0x20 );
  LcdWrite(LCD_C, 0x0C );
}




void LcdString(const char *characters)
{
  while (*characters)
  {
    LcdCharacter(*characters++);
  }
}

void LcdWrite(byte dc, byte data)
{
  digitalWrite(PIN_DC, dc);
  digitalWrite(PIN_SCE, LOW);
  shiftOut(PIN_SDIN, PIN_SCLK, MSBFIRST, data);
  digitalWrite(PIN_SCE, HIGH);
}

//---------------------------------------END LCD NOKIA3310


void setup(void) { 

 
  Serial.begin(9600); 
//Wire.begin(); 
 dps.init(MODE_ULTRA_HIGHRES, 0, true); 
 // dps.init();
 pinMode(13, OUTPUT);


//--------------------------------------------
 LcdInitialise();
  LcdClear();
//-------------------------------------------- 

  /* Initialize a new chip by turning off write protection and clearing the
     clock halt flag. These methods needn't always be called. See the DS1302
     datasheet for details. */
  rtc.write_protect(false);
  rtc.halt(false);

  /* Make a new time object to set the date and time */
  /*   Tuesday, May 19, 2009 at 21:16:37.            */
//Time t(2015, 9, 23, 9, 51, 00, 4);

  /* Set the time and date on the chip */
// rtc.time(t);

  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(9);

}          

void loop(void) { 

  
 DHT.read11(dht_dpin);

  
  dps.getPressure(&Pressure); 
  dps.getAltitude(&Altitude); 
  dps.getTemperature(&Temperature);

  
   if (Serial.available() > 0) {  //если пришли данные
    incomingByte = Serial.read(); // считываем байт
    if(incomingByte == '0') {
       digitalWrite(13, LOW);  // если 1, то выключаем LED
       }
    if(incomingByte == '1') {
       digitalWrite(13, HIGH); // если 0, то включаем LED
     }
   }

 if (DHT.temperature<19)
  {
digitalWrite(13, HIGH);    // turn the LED off by making the voltage LOW
  }
   if (DHT.temperature>=22)
  {
digitalWrite(13, LOW);   // turn the LED on (HIGH is the voltage level)
  }
  
 Serial.print("  Alt(m):"); 
 Serial.print(Altitude/100); 
 Serial.print("  Pressure(mm Hg):"); 
 Serial.print(Pressure/133.3); 
 Serial.print(" Temp1:"); 
 Serial.println(Temperature*0.1); 
 Serial.print(" H:");
 Serial.print(DHT.humidity);
 Serial.print(" Temp2:");
 Serial.println(DHT.temperature);
 
  print_time();

LcdClear();

gotoXY(0,0);

Time t = rtc.time();
// sun mon tue wed thu fri sat
char day[3];
switch (t.day) {
    case 1:
      strcpy(day, "SUN");
      break;
    case 2:
      strcpy(day, "MON");
      break;
    case 3:
      strcpy(day, "TUE");
      break;
    case 4:
      strcpy(day, "WED");
      break;
    case 5:
      strcpy(day, "THU");
      break;
    case 6:
      strcpy(day, "FRI");
      break;
    case 7:
      strcpy(day, "SAT");
      break;
  }

  LcdString(day);

char strdat[11];

  LcdString(" ");  
  if (t.date<10){LcdString("0");}
    sprintf(strdat, "%u",t.date);
    LcdString(strdat);
    LcdString(".");
    if (t.mon<10){LcdString("0");}
     sprintf(strdat, "%u",t.mon);
    LcdString(strdat);
    LcdString(".");
   
     sprintf(strdat, "%u",t.yr-2000);
    LcdString(strdat);
 
//           t.yr, t.mon, t.date,

gotoXY(0,1);

char strtime[11];

    if (t.hr<10){LcdString("0");}
    sprintf(strtime, "%u",t.hr);
    LcdString(strtime);
    LcdString(":");
    if (t.min<10){LcdString("0");}
     sprintf(strtime, "%u",t.min);
    LcdString(strtime);
    LcdString(":");
    if (t.sec<10){LcdString("0");}
     sprintf(strtime, "%u ",t.sec);
    LcdString(strtime);

 char strr[11];
 int number1 = DHT.humidity;

    sprintf(strr, "%u", number1);
    LcdString(strr);
    LcdString("%");


 gotoXY(0,2);
 
    LcdString("");
char strrr[11];
   int number2 = Temperature*0.1;
    sprintf(strrr, "%u", number2);
    LcdString(strrr);
    LcdString(".");
    
 long temp1=Temperature*0.1*10;
 int temp2=Temperature*0.1;
 temp2=temp2*10;
 int temp3=temp1-temp2; 
   char stttrr[11];
    sprintf(stttrr, "%u(", temp3);
    LcdString(stttrr);

char str[11];
 int number13 = DHT.temperature;

    sprintf(str, "%u", number13);
    LcdString(str);

LcdString(")C");

        
 gotoXY(0,3);
   LcdString("");
   char strrrr[11];
   int number3 = Pressure/133.3;
    sprintf(strrrr, "%u", number3);
    LcdString(strrrr);
    LcdString(".");
    
 double pr1=Pressure/133.3*100;
 int pr2=Pressure/133.3;
 pr2=pr2*100;
 int pr3=pr1-pr2; 
 if (pr3<10)
 {
 LcdString("0");
 }
   char sttrrr[11];
    sprintf(sttrrr, "%u", pr3);
    LcdString(sttrrr);
         LcdString("mm");
   gotoXY(0,4);

 delay(1000); 
}
