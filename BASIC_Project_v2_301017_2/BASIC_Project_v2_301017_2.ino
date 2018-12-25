#include <RCSwitch.h>
char incomingByte; 
RCSwitch mySwitch = RCSwitch();
#include <EEPROM.h> 
#include <RemoteReceiver.h>
#include <RemoteTransmitter.h>
//---------------------------------------LCD NOKIA3310 add test for git
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


//---------------------------------------LCD NOKIA3310
static const byte ASCII[][5] =
{
 {0x00, 0x00, 0x00, 0x00, 0x00} // 20  
,{0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
,{0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
,{0x2a, 0x1c, 0x7f, 0x1c, 0x2a} // 23 # сонце. було 0x14, 0x7f, 0x14, 0x7f, 0x14
,{0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
,{0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
,{0x0c, 0x36, 0x78, 0x5c, 0x2f} // 26 &  вогник. було 0x36, 0x49, 0x55, 0x22, 0x50 
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
,{0x2a, 0x57, 0x2f, 0x57, 0x2e} // 5e ^ хмарка. було - 0x04, 0x02, 0x01, 0x02, 0x04
,{0x38, 0x74, 0x7f, 0x7e, 0x38} // 5f _ капля. було - 0x40, 0x40, 0x40, 0x40, 0x40
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
,{0x04, 0x02, 0x7f, 0x02, 0x04} // 7b {    up. було- 0x00, 0x08, 0x36, 0x41, 0x00
,{0x00, 0x00, 0x7f, 0x00, 0x00} // 7c |
,{0x10, 0x20, 0x7f, 0x20, 0x10} // 7d }   done. було-  0x00, 0x41, 0x36, 0x08, 0x00
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

void showCode(unsigned long receivedCode, unsigned int period) {
  // Note: interrupts are disabled. You can re-enable them if needed.
  
  // Print the received code.
  Serial.print("Code: ");
  Serial.print(receivedCode);
  Serial.print(", period duration: ");
  Serial.print(period);
  Serial.println("us.");
}

void setup(void) { 
 RemoteReceiver::init(0, 3, showCode);
 
if (EEPROM.read(101) < 5 || EEPROM.read(101) > 29){
 int MinTempProg1=19;
 EEPROM.write(101, MinTempProg1);
}
if (EEPROM.read(102) < 5 || EEPROM.read(102) > 29){
 int MaxTempProg1=21;
 EEPROM.write(102, MaxTempProg1);
}

 
if (EEPROM.read(99) < 10 || EEPROM.read(99) > 99){
 int Pass=99;
 EEPROM.write(99, Pass);
}
if (EEPROM.read(100) < 10 || EEPROM.read(100) > 100){
int Rezh=10;
 EEPROM.write(100, Rezh);
}
  pinMode(led, OUTPUT);
  Serial.begin(9600); 
//Wire.begin(); 
  delay(1000);

   
//  dps.init(MODE_ULTRA_HIGHRES, 0, true); 
 // dps.init();


//--------------------------------------------
 LcdInitialise();
  LcdClear();
  gotoXY (0,0);
  LcdString("V2.2.301017");
  delay(1000);
//-------------------------------------------- 

  /* Initialize a new chip by turning off write protection and clearing the
     clock halt flag. These methods needn't always be called. See the DS1302
     datasheet for details. */
  rtc.write_protect(false);
  rtc.halt(false);

  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(9);

}     
//------------------end setup

//----------------------------------------------------------------------GET_EEPROM
int GetDataProg (int w, int prog, int type){
int D;
int Addr;
int t1;
switch (w) {
 case 1:
    Addr = 0;
    break;
 case 2:
    Addr = 4;
    break;
 case 3:
    Addr = 8;
    break;
 case 4:
    Addr = 12;
    break;
 case 5:
    Addr = 16;
    break;
case 6:
    Addr = 20;
    break;
case 7:
    Addr = 24;
    break;
default:
    Addr = 0;
  }
switch (type) {
 case 1:
    t1 = 1;
    break;
 case 2:
    t1 = 29;
    break;
 case 3:
    t1 = 57;
    break;
    default:
    t1 = 1;
}

D=EEPROM.read(Addr+t1+prog);
  return D;
}
//----------------------------------------------------------------------SET_EEPROM
void SetDataProg (int w, int prog, int type, int D){
int Addr;
int t1;
switch (w) {
 case 1:
    Addr = 0;
    break;
 case 2:
    Addr = 4;
    break;
 case 3:
    Addr = 8;
    break;
 case 4:
    Addr = 12;
    break;
 case 5:
    Addr = 16;
    break;
case 6:
    Addr = 20;
    break;
case 7:
    Addr = 24;
    break;
default:
    Addr = 0;
  }
  switch (type) {
 case 1:
    t1 = 1;
    break;
 case 2:
    t1 = 29;
    break;
 case 3:
    t1 = 57;
    break;
    default:
    t1 = 1;
}
EEPROM.write(Addr+t1+prog,D);
}


//-------------------------------
//---------------------
void LcdNum (int y){
char st[11];
    sprintf(st, "%u", y);
    LcdString(st);  
}
 
//------------------------
int byteToint (int x){
int result;
int i=48;
int ii=0;
while (i<=57){
if (x==i) {
  result=ii;
  return result;
  }
i=i+1;
ii=ii+1;
}
}
//----------------------------------
int d13;
int Rezh = EEPROM.read(100);  
int Press1 = 0;
int Press2 = 0;
int Press3 = 0;
int sett1=0;
int p1=0;
int p2=0;
int p3=0;
int delta1=0;
int delta2=0;
int delta3=0;
int H11;
int M11;
int W11;
int w;
int timeh1;
int timem1;
int temper1;
int timeh2;
int timem2;
int temper2;
int timeh3;
int timem3;
int temper3;
int timeh4;
int timem4;
int temper4;
int SumWorkHors=0;
int SumWorkMin=0;
int SumWorkSec=0;


int t1;
//----------------------------------------------

void StartFire (){
  digitalWrite(13, HIGH);
    d13=11;
    RemoteTransmitter::sendCode(9, 442500, 149, 3); //ON
     delay(3000);
    RemoteTransmitter::sendCode(9, 500743, 486, 3); //ON - kotel
     delay(3000);
  }
void StopFire (){
 digitalWrite(13, LOW);
   d13=10;
 RemoteTransmitter::sendCode(9, 500745, 486, 3); //OFF - kotel 
 delay(3000);
 RemoteTransmitter::sendCode(9, 442496, 149, 3); //OFF - nasos
  }

//------------------------------------------------

void loop(void) { 

 DHT.read11(dht_dpin);

//----------------------------------------------------------
   if (Serial.available() > 0) 
 {  //если пришли данные
    incomingByte = Serial.read(); // считываем бай
  

    if(incomingByte == '0') {
    
  char incomingBytes[2];
Serial.readBytes(incomingBytes,2);
int pass1 = byteToint(incomingBytes[0]);
int pass2 = byteToint(incomingBytes[1]);                
int pass0=pass1*10+pass2;
int passE=EEPROM.read(99);

if (passE==pass0){
    LcdClear();
  gotoXY (0,0);
  LcdString("System OFF");
  gotoXY (0,1);
  LcdString("HAND SETTING");
      digitalWrite(13, LOW);  // если 1, то включаем LED
  Rezh=10;
  EEPROM.write(100, Rezh);
     Serial.println("LED OFF!");  // и выводим обратно сообщение
StopFire ();
    }
 else if(passE!=pass0){
      LcdClear();
  gotoXY (0,0);
  LcdString("NOT OFF");
  gotoXY (0,1);
  LcdString("WRONG PASSW!");
      } 
  delay(5000);     
    }
//-------------------------------------------------------------------------------------- 
 if(incomingByte == '2') {
  char incomingBytes[15];
Serial.readBytes(incomingBytes,15);
     int y1 = byteToint(incomingBytes[0]);
     int y2 = byteToint(incomingBytes[1]);
     int y3 = byteToint(incomingBytes[2]);
     int y4 = byteToint(incomingBytes[3]);
int y=y1*1000+y2*100+y3*10+y4;

     int m1 = byteToint(incomingBytes[4]);
     int m2 = byteToint(incomingBytes[5]);
int m=m2;
     if (m1==1){m=m1*10+m2;}

     int d1 = byteToint(incomingBytes[6]);
     int d2 = byteToint(incomingBytes[7]);
int d=d2;
     if (d1>0) {d=d1*10+d2;} 
          
     int h1 = byteToint(incomingBytes[8]);
     int h2 = byteToint(incomingBytes[9]);
int h=h2;
    if(h1>0){h=h1*10+h2;}
    
    int hv1 = byteToint(incomingBytes[10]);
    int hv2 = byteToint(incomingBytes[11]);
int hv=hv2;
    if(hv1>0){hv=hv1*10+hv2;}

int dn = byteToint(incomingBytes[12]);          

int pass1 = byteToint(incomingBytes[13]);
int pass2 = byteToint(incomingBytes[14]);                
int pass0=pass1*10+pass2;
int passE=EEPROM.read(99);

if (passE==pass0){
Time t(y, m, d, h, hv, 00, dn);
  /* Set the time and date on the chip */
  rtc.time(t);
Serial.println("SET Clock...");
 LcdClear();
  gotoXY (0,0);
  LcdString("SET Clock...Ok!");      
}
    else if(passE!=pass0){
      LcdClear();
  gotoXY (0,0);
  LcdString("SET Clock...");
  gotoXY (0,1);
  LcdString("WRONG PASSW!");
   gotoXY (0,2);
   LcdString("------------");  
  gotoXY (0,3);
  LcdString(">2YYYYMMDD");
  gotoXY (0,4);
  LcdString("HHMMWPP");
  gotoXY (0,5);
  LcdString("W-SUN=1");
      } 
     delay(5000);  
      }
 
 //------------------------------------------------------------------------------------------


 if (incomingByte == '1') {
  char incomingBytes[6];
Serial.readBytes(incomingBytes,6);
int pass1 = byteToint(incomingBytes[4]);
int pass2 = byteToint(incomingBytes[5]);                
int pass0=pass1*10+pass2;
int passE=EEPROM.read(99);
int temper1;
int temper2;
if (passE==pass0){
  int temper11 = byteToint(incomingBytes[0]);
  int temper12 = byteToint(incomingBytes[1]);
  if (temper11>2) {temper11=2;}
  if (temper11<=2) {temper1=temper11*10+temper12;}
  if (temper11<=0&&temper12<5){temper1=5;}
 
  int temper21 = byteToint(incomingBytes[2]);
  int temper22 = byteToint(incomingBytes[3]);
if (temper21>2) {temper21=2;}
  if (temper21<=2) {temper2=temper21*10+temper22;}
  if (temper21<=0&&temper22<7){temper2=7;}

if (temper1<temper2){
  
  EEPROM.write(101,temper1);
  EEPROM.write(102,temper2);
  sett1=11;
 
}
if (temper1>=temper2){
 sett1=10;
}

   if (sett1==11){
       gotoXY (0,3);
  LcdString("SET NEW TEMP");
      }
      if (sett1==10){
  gotoXY (0,3);
  LcdString("NO SET TEMP!");
      }
  }

if (passE!=pass0){
int pass1 = byteToint(incomingBytes[0]);
int pass2 = byteToint(incomingBytes[1]);                
int pass0=pass1*10+pass2;
if (passE==pass0){

  LcdClear();
  gotoXY (0,0);
  LcdString("ON - PROG 1 ");
  gotoXY(0,1);
  LcdString("MinTemp: ");
 LcdNum(EEPROM.read(101));
      gotoXY(0,2);
  LcdString("MaxTemp: ");
LcdNum(EEPROM.read(102));
    Rezh=11; 
    EEPROM.write(100, Rezh);
}
}
  delay(5000); 
 }
//-------------------------------------------


 if (incomingByte == '3') {
   int w=1;
  char incomingBytes[26];

Serial.readBytes(incomingBytes,26);


int pass1 = byteToint(incomingBytes[24]);
int pass2 = byteToint(incomingBytes[25]);                
int pass0=pass1*10+pass2;
int passE=EEPROM.read(99);
timeh1 = byteToint(incomingBytes[0])*10+byteToint(incomingBytes[1]);
timem1 = byteToint(incomingBytes[2])*10+byteToint(incomingBytes[3]);
temper1 = byteToint(incomingBytes[4])*10+byteToint(incomingBytes[5]); 
timeh2 = byteToint(incomingBytes[6])*10+byteToint(incomingBytes[7]);
timem2 = byteToint(incomingBytes[8])*10+byteToint(incomingBytes[9]);
temper2 = byteToint(incomingBytes[10])*10+byteToint(incomingBytes[11]);
timeh3 = byteToint(incomingBytes[12])*10+byteToint(incomingBytes[13]);
timem3 = byteToint(incomingBytes[14])*10+byteToint(incomingBytes[15]);
temper3 = byteToint(incomingBytes[16])*10+byteToint(incomingBytes[17]);
timeh4 = byteToint(incomingBytes[18])*10+byteToint(incomingBytes[19]);
timem4 = byteToint(incomingBytes[20])*10+byteToint(incomingBytes[21]);
temper4 = byteToint(incomingBytes[22])*10+byteToint(incomingBytes[23]);

if (passE==pass0){
  
SetDataProg(w,1,1,timeh1);
SetDataProg(w,1,2,timem1);
SetDataProg(w,1,3,temper1);  
SetDataProg(w,2,1,timeh2);
SetDataProg(w,2,2,timem2);
SetDataProg(w,2,3,temper2);  
SetDataProg(w,3,1,timeh3);
SetDataProg(w,3,2,timem3);
SetDataProg(w,3,3,temper3);  
SetDataProg(w,4,1,timeh4);
SetDataProg(w,4,2,timem4);
SetDataProg(w,4,3,temper4);  

 LcdClear();
  gotoXY (0,0);
  LcdString("SET1 AUTO OK");
  
}


else if(passE!=pass0){
      LcdClear();
  gotoXY (0,0);
  LcdString("NO SET AUTO");
  gotoXY (0,1);
  LcdString("WRONG PASSW!");
      } 
      
  LcdClear();
  gotoXY (0,0);
  LcdString("ON - AUTO 1");
    Rezh=21; 
EEPROM.write(100, Rezh);

 delay(5000); 

 
 }
 
 
 if (incomingByte == '4') {
   int w=2;
  char incomingBytes[26];

Serial.readBytes(incomingBytes,26);


int pass1 = byteToint(incomingBytes[24]);
int pass2 = byteToint(incomingBytes[25]);                
int pass0=pass1*10+pass2;
int passE=EEPROM.read(99);
int timeh1 = byteToint(incomingBytes[0])*10+byteToint(incomingBytes[1]);
int timem1 = byteToint(incomingBytes[2])*10+byteToint(incomingBytes[3]);
int temper1 = byteToint(incomingBytes[4])*10+byteToint(incomingBytes[5]); 
int timeh2 = byteToint(incomingBytes[6])*10+byteToint(incomingBytes[7]);
int timem2 = byteToint(incomingBytes[8])*10+byteToint(incomingBytes[9]);
int temper2 = byteToint(incomingBytes[10])*10+byteToint(incomingBytes[11]);
int timeh3 = byteToint(incomingBytes[12])*10+byteToint(incomingBytes[13]);
int timem3 = byteToint(incomingBytes[14])*10+byteToint(incomingBytes[15]);
int temper3 = byteToint(incomingBytes[16])*10+byteToint(incomingBytes[17]);
int timeh4 = byteToint(incomingBytes[18])*10+byteToint(incomingBytes[19]);
int timem4 = byteToint(incomingBytes[20])*10+byteToint(incomingBytes[21]);
int temper4 = byteToint(incomingBytes[22])*10+byteToint(incomingBytes[23]);

if (passE==pass0){
  
SetDataProg(w,1,1,timeh1);
SetDataProg(w,1,2,timem1);
SetDataProg(w,1,3,temper1);  
SetDataProg(w,2,1,timeh2);
SetDataProg(w,2,2,timem2);
SetDataProg(w,2,3,temper2);  
SetDataProg(w,3,1,timeh3);
SetDataProg(w,3,2,timem3);
SetDataProg(w,3,3,temper3);  
SetDataProg(w,4,1,timeh4);
SetDataProg(w,4,2,timem4);
SetDataProg(w,4,3,temper4);  

 LcdClear();
  gotoXY (0,0);
  LcdString("SET2 AUTO OK");
  
}


else if(passE!=pass0){
      LcdClear();
  gotoXY (0,0);
  LcdString("NO SET2 AUTO");
  gotoXY (0,1);
  LcdString("WRONG PASSW!");
      } 
      
  LcdClear();
  gotoXY (0,0);
  LcdString("ON - AUTO 2");
    Rezh=21; 
EEPROM.write(100, Rezh);

 delay(5000); 

 
 }
 
 if (incomingByte == '5') {
   int w=3;
  char incomingBytes[26];

Serial.readBytes(incomingBytes,26);


int pass1 = byteToint(incomingBytes[24]);
int pass2 = byteToint(incomingBytes[25]);                
int pass0=pass1*10+pass2;
int passE=EEPROM.read(99);
int timeh1 = byteToint(incomingBytes[0])*10+byteToint(incomingBytes[1]);
int timem1 = byteToint(incomingBytes[2])*10+byteToint(incomingBytes[3]);
int temper1 = byteToint(incomingBytes[4])*10+byteToint(incomingBytes[5]); 
int timeh2 = byteToint(incomingBytes[6])*10+byteToint(incomingBytes[7]);
int timem2 = byteToint(incomingBytes[8])*10+byteToint(incomingBytes[9]);
int temper2 = byteToint(incomingBytes[10])*10+byteToint(incomingBytes[11]);
int timeh3 = byteToint(incomingBytes[12])*10+byteToint(incomingBytes[13]);
int timem3 = byteToint(incomingBytes[14])*10+byteToint(incomingBytes[15]);
int temper3 = byteToint(incomingBytes[16])*10+byteToint(incomingBytes[17]);
int timeh4 = byteToint(incomingBytes[18])*10+byteToint(incomingBytes[19]);
int timem4 = byteToint(incomingBytes[20])*10+byteToint(incomingBytes[21]);
int temper4 = byteToint(incomingBytes[22])*10+byteToint(incomingBytes[23]);

if (passE==pass0){
  
SetDataProg(w,1,1,timeh1);
SetDataProg(w,1,2,timem1);
SetDataProg(w,1,3,temper1);  
SetDataProg(w,2,1,timeh2);
SetDataProg(w,2,2,timem2);
SetDataProg(w,2,3,temper2);  
SetDataProg(w,3,1,timeh3);
SetDataProg(w,3,2,timem3);
SetDataProg(w,3,3,temper3);  
SetDataProg(w,4,1,timeh4);
SetDataProg(w,4,2,timem4);
SetDataProg(w,4,3,temper4);  

 LcdClear();
  gotoXY (0,0);
  LcdString("SET3 AUTO OK");
  
}


else if(passE!=pass0){
      LcdClear();
  gotoXY (0,0);
  LcdString("NO SET3 AUTO");
  gotoXY (0,1);
  LcdString("WRONG PASSW!");
      } 
      
  LcdClear();
  gotoXY (0,0);
  LcdString("ON - AUTO 3");
    Rezh=21; 
EEPROM.write(100, Rezh);

 delay(5000); 

 
 }
 
 
 if (incomingByte == '6') {
   int w=4;
  char incomingBytes[26];

Serial.readBytes(incomingBytes,26);


int pass1 = byteToint(incomingBytes[24]);
int pass2 = byteToint(incomingBytes[25]);                
int pass0=pass1*10+pass2;
int passE=EEPROM.read(99);
int timeh1 = byteToint(incomingBytes[0])*10+byteToint(incomingBytes[1]);
int timem1 = byteToint(incomingBytes[2])*10+byteToint(incomingBytes[3]);
int temper1 = byteToint(incomingBytes[4])*10+byteToint(incomingBytes[5]); 
int timeh2 = byteToint(incomingBytes[6])*10+byteToint(incomingBytes[7]);
int timem2 = byteToint(incomingBytes[8])*10+byteToint(incomingBytes[9]);
int temper2 = byteToint(incomingBytes[10])*10+byteToint(incomingBytes[11]);
int timeh3 = byteToint(incomingBytes[12])*10+byteToint(incomingBytes[13]);
int timem3 = byteToint(incomingBytes[14])*10+byteToint(incomingBytes[15]);
int temper3 = byteToint(incomingBytes[16])*10+byteToint(incomingBytes[17]);
int timeh4 = byteToint(incomingBytes[18])*10+byteToint(incomingBytes[19]);
int timem4 = byteToint(incomingBytes[20])*10+byteToint(incomingBytes[21]);
int temper4 = byteToint(incomingBytes[22])*10+byteToint(incomingBytes[23]);

if (passE==pass0){
  
SetDataProg(w,1,1,timeh1);
SetDataProg(w,1,2,timem1);
SetDataProg(w,1,3,temper1);  
SetDataProg(w,2,1,timeh2);
SetDataProg(w,2,2,timem2);
SetDataProg(w,2,3,temper2);  
SetDataProg(w,3,1,timeh3);
SetDataProg(w,3,2,timem3);
SetDataProg(w,3,3,temper3);  
SetDataProg(w,4,1,timeh4);
SetDataProg(w,4,2,timem4);
SetDataProg(w,4,3,temper4);  

 LcdClear();
  gotoXY (0,0);
  LcdString("SET4 AUTO OK");
  
}


else if(passE!=pass0){
      LcdClear();
  gotoXY (0,0);
  LcdString("NO SET4 AUTO");
  gotoXY (0,1);
  LcdString("WRONG PASSW!");
      } 
      
  LcdClear();
  gotoXY (0,0);
  LcdString("ON - AUTO 4");
    Rezh=21; 
EEPROM.write(100, Rezh);

 delay(5000); 

 
 }
 
 if (incomingByte == '7') {
   int w=5;
  char incomingBytes[26];

Serial.readBytes(incomingBytes,26);


int pass1 = byteToint(incomingBytes[24]);
int pass2 = byteToint(incomingBytes[25]);                
int pass0=pass1*10+pass2;
int passE=EEPROM.read(99);
int timeh1 = byteToint(incomingBytes[0])*10+byteToint(incomingBytes[1]);
int timem1 = byteToint(incomingBytes[2])*10+byteToint(incomingBytes[3]);
int temper1 = byteToint(incomingBytes[4])*10+byteToint(incomingBytes[5]); 
int timeh2 = byteToint(incomingBytes[6])*10+byteToint(incomingBytes[7]);
int timem2 = byteToint(incomingBytes[8])*10+byteToint(incomingBytes[9]);
int temper2 = byteToint(incomingBytes[10])*10+byteToint(incomingBytes[11]);
int timeh3 = byteToint(incomingBytes[12])*10+byteToint(incomingBytes[13]);
int timem3 = byteToint(incomingBytes[14])*10+byteToint(incomingBytes[15]);
int temper3 = byteToint(incomingBytes[16])*10+byteToint(incomingBytes[17]);
int timeh4 = byteToint(incomingBytes[18])*10+byteToint(incomingBytes[19]);
int timem4 = byteToint(incomingBytes[20])*10+byteToint(incomingBytes[21]);
int temper4 = byteToint(incomingBytes[22])*10+byteToint(incomingBytes[23]);

if (passE==pass0){
  
SetDataProg(w,1,1,timeh1);
SetDataProg(w,1,2,timem1);
SetDataProg(w,1,3,temper1);  
SetDataProg(w,2,1,timeh2);
SetDataProg(w,2,2,timem2);
SetDataProg(w,2,3,temper2);  
SetDataProg(w,3,1,timeh3);
SetDataProg(w,3,2,timem3);
SetDataProg(w,3,3,temper3);  
SetDataProg(w,4,1,timeh4);
SetDataProg(w,4,2,timem4);
SetDataProg(w,4,3,temper4);  

 LcdClear();
  gotoXY (0,0);
  LcdString("SET5 AUTO OK");
  
}


else if(passE!=pass0){
      LcdClear();
  gotoXY (0,0);
  LcdString("NO SET5 AUTO");
  gotoXY (0,1);
  LcdString("WRONG PASSW!");
      } 
      
  LcdClear();
  gotoXY (0,0);
  LcdString("ON - AUTO 5");
    Rezh=21; 
EEPROM.write(100, Rezh);

 delay(5000); 

 
 }
 
 if (incomingByte == '8') {
   int w=6;
  char incomingBytes[26];

Serial.readBytes(incomingBytes,26);

int pass1 = byteToint(incomingBytes[24]);
int pass2 = byteToint(incomingBytes[25]);                
int pass0=pass1*10+pass2;
int passE=EEPROM.read(99);
int timeh1 = byteToint(incomingBytes[0])*10+byteToint(incomingBytes[1]);
int timem1 = byteToint(incomingBytes[2])*10+byteToint(incomingBytes[3]);
int temper1 = byteToint(incomingBytes[4])*10+byteToint(incomingBytes[5]); 
int timeh2 = byteToint(incomingBytes[6])*10+byteToint(incomingBytes[7]);
int timem2 = byteToint(incomingBytes[8])*10+byteToint(incomingBytes[9]);
int temper2 = byteToint(incomingBytes[10])*10+byteToint(incomingBytes[11]);
int timeh3 = byteToint(incomingBytes[12])*10+byteToint(incomingBytes[13]);
int timem3 = byteToint(incomingBytes[14])*10+byteToint(incomingBytes[15]);
int temper3 = byteToint(incomingBytes[16])*10+byteToint(incomingBytes[17]);
int timeh4 = byteToint(incomingBytes[18])*10+byteToint(incomingBytes[19]);
int timem4 = byteToint(incomingBytes[20])*10+byteToint(incomingBytes[21]);
int temper4 = byteToint(incomingBytes[22])*10+byteToint(incomingBytes[23]);

if (passE==pass0){
  
SetDataProg(w,1,1,timeh1);
SetDataProg(w,1,2,timem1);
SetDataProg(w,1,3,temper1);  
SetDataProg(w,2,1,timeh2);
SetDataProg(w,2,2,timem2);
SetDataProg(w,2,3,temper2);  
SetDataProg(w,3,1,timeh3);
SetDataProg(w,3,2,timem3);
SetDataProg(w,3,3,temper3);  
SetDataProg(w,4,1,timeh4);
SetDataProg(w,4,2,timem4);
SetDataProg(w,4,3,temper4);  

 LcdClear();
  gotoXY (0,0);
  LcdString("SET6 AUTO OK");
  
}


else if(passE!=pass0){
      LcdClear();
  gotoXY (0,0);
  LcdString("NO SET6 AUTO");
  gotoXY (0,1);
  LcdString("WRONG PASSW!");
      } 
      
  LcdClear();
  gotoXY (0,0);
  LcdString("ON - AUTO 6");
    Rezh=21; 
EEPROM.write(100, Rezh);

 delay(5000); 

 
 }
 
if (incomingByte == '9') {
   int w=7;
  char incomingBytes[26];

Serial.readBytes(incomingBytes,26);


int pass1 = byteToint(incomingBytes[24]);
int pass2 = byteToint(incomingBytes[25]);                
int pass0=pass1*10+pass2;
int passE=EEPROM.read(99);
int timeh1 = byteToint(incomingBytes[0])*10+byteToint(incomingBytes[1]);
int timem1 = byteToint(incomingBytes[2])*10+byteToint(incomingBytes[3]);
int temper1 = byteToint(incomingBytes[4])*10+byteToint(incomingBytes[5]); 
int timeh2 = byteToint(incomingBytes[6])*10+byteToint(incomingBytes[7]);
int timem2 = byteToint(incomingBytes[8])*10+byteToint(incomingBytes[9]);
int temper2 = byteToint(incomingBytes[10])*10+byteToint(incomingBytes[11]);
int timeh3 = byteToint(incomingBytes[12])*10+byteToint(incomingBytes[13]);
int timem3 = byteToint(incomingBytes[14])*10+byteToint(incomingBytes[15]);
int temper3 = byteToint(incomingBytes[16])*10+byteToint(incomingBytes[17]);
int timeh4 = byteToint(incomingBytes[18])*10+byteToint(incomingBytes[19]);
int timem4 = byteToint(incomingBytes[20])*10+byteToint(incomingBytes[21]);
int temper4 = byteToint(incomingBytes[22])*10+byteToint(incomingBytes[23]);

if (passE==pass0){
  
SetDataProg(w,1,1,timeh1);
SetDataProg(w,1,2,timem1);
SetDataProg(w,1,3,temper1);  
SetDataProg(w,2,1,timeh2);
SetDataProg(w,2,2,timem2);
SetDataProg(w,2,3,temper2);  
SetDataProg(w,3,1,timeh3);
SetDataProg(w,3,2,timem3);
SetDataProg(w,3,3,temper3);  
SetDataProg(w,4,1,timeh4);
SetDataProg(w,4,2,timem4);
SetDataProg(w,4,3,temper4);  

 LcdClear();
  gotoXY (0,0);
  LcdString("SET7 AUTO OK");
  
}


else if(passE!=pass0){
      LcdClear();
  gotoXY (0,0);
  LcdString("NO SET7 AUTO");
  gotoXY (0,1);
  LcdString("WRONG PASSW!");
      } 
      
  LcdClear();
  gotoXY (0,0);
  LcdString("ON - AUTO 7");
    Rezh=21; 
EEPROM.write(100, Rezh);

 delay(5000); 

 
 } 
 
  
 }
//-------------------------------------------------------------------------------------------------------------------------

if (d13==11){
Serial.print("F-ON");
}
if (d13==10){
Serial.println("F-OFF");
}
Serial.print("R-"); 
if (Rezh==10){
   Serial.println("OFF");
}
if (Rezh==11){
   Serial.println("H");
}
if (Rezh>=21){
   Serial.println("A");
}

Serial.print("Temp:"); 
Serial.print(DHT.temperature); 
Serial.print(" HUM:"); 
Serial.println(DHT.humidity);
 
print_time();
  
LcdClear();

gotoXY(0,0);

Time t = rtc.time();

H11=t.hr;
M11=t.min;
W11=t.day;
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
  LcdString(" ");  
  if (t.date<10){LcdString("0");}
    LcdNum(t.date);
    LcdString(".");
    if (t.mon<10){LcdString("0");}
    LcdNum(t.mon);
    LcdString(".");
    LcdNum(t.yr-2000);
 
//  t.yr, t.mon, t.date,

gotoXY(0,1);

    if (t.hr<10){LcdString("0");}
    LcdNum(t.hr);
    LcdString(":");
    if (t.min<10){LcdString("0");}
    LcdNum(t.min);
    LcdString(":");
    if (t.sec<10){LcdString("0");}
    LcdNum(t.sec);

LcdString("_");
LcdNum(DHT.humidity);
LcdString("%");


gotoXY(0,2);
 
LcdString("     ");
LcdNum(DHT.temperature);
LcdString("C");
gotoXY(0,3);
LcdString("WT:");
if (SumWorkHors<10){
  LcdString("0");
  }
LcdNum(SumWorkHors);
LcdString(":");
if(SumWorkMin<10){
   LcdString("0");
  }
LcdNum(SumWorkMin);
LcdString(":");
if(SumWorkSec<10){
   LcdString("0");
  }
LcdNum(SumWorkSec);

if (d13==10){LcdString("*");}

if (d13==11){LcdString("&");
SumWorkSec=SumWorkSec+1;
if (SumWorkSec==60){
SumWorkMin=SumWorkMin+1;
SumWorkSec=0;
}
if (SumWorkMin==60){
  SumWorkHors=SumWorkHors+1;
  SumWorkMin=0;
  }
}
LcdString("");

//-------------------------------

if (Rezh==10){
    gotoXY (0,4);
  LcdString("System OFF");
  gotoXY (0,5);
  LcdString("Temp:5-7");
  }
 
if (Rezh==11){
    gotoXY (0,4);
  LcdString("PROG1 - ON");
  gotoXY (0,5);
  LcdString("Temp:");
LcdNum(EEPROM.read(101));
 LcdString("-");
LcdNum(EEPROM.read(102));
  }

 if (Rezh==21){
 
  gotoXY (0,4);

switch (W11) {
    case 1:
  LcdString("S");
      break;
    case 2:
  LcdString("M");
      break;
    case 3:
  LcdString("T");
      break;
    case 4:
  LcdString("W");
      break;
    case 5:
  LcdString("T");
      break;
    case 6:
  LcdString("F");
      break;
    case 7:
  LcdString("S");
      break;
  }

 

if (GetDataProg(W11,1,1)<10){
LcdString("0");
}
LcdNum(timeh1=GetDataProg(W11,1,1));

LcdString("-");

if (GetDataProg(W11,2,1)<10){
LcdString("0");
}
LcdNum(timeh2=GetDataProg(W11,2,1));

LcdString("-");

if (GetDataProg(W11,3,1)<10){
LcdString("0");
}
LcdNum(timeh3=GetDataProg(W11,3,1));

LcdString("-");

if (GetDataProg(W11,4,1)<10){
LcdString("0");
}
LcdNum(timeh4=GetDataProg(W11,4,1));

gotoXY (0,5);
LcdString(" ");

if (GetDataProg(W11,1,3)<10){
LcdString("0");
}
LcdNum(temper1=GetDataProg(W11,1,3));

LcdString("-");

if (GetDataProg(W11,2,3)<10){
LcdString("0");
}
LcdNum(temper2=GetDataProg(W11,2,3));

LcdString("-");

if (GetDataProg(W11,3,3)<10){
LcdString("0");
}
LcdNum(temper3=GetDataProg(W11,3,3));

LcdString("-");

if (GetDataProg(W11,4,3)<10){
LcdString("0");
}
LcdNum(temper4=GetDataProg(W11,4,3));
}
  
  // DO IT!--------------------------------------------------------
  
if (Rezh==10)
{
  int TempA = DHT.temperature;
if (TempA<=5){
  StartFire ();
    }
if (TempA>7){
   StopFire ();
    }     
    }

if (Rezh==11)
{
int TempA = DHT.temperature;
if (TempA <=EEPROM.read(101)){
   StartFire ();
   
  }
if (TempA >=EEPROM.read(102)){
    StopFire (); 
  }
Serial.print("Temp_F:"); 
Serial.print(EEPROM.read(101));
Serial.print("-"); 
Serial.println(EEPROM.read(102)); 
}



if (Rezh==21){
  //-----------------------------------------------------------------------------------------------DO IT!
  int TempA = DHT.temperature;
if(H11>=timeh1&&H11<timeh2){
if(TempA<=(temper1-1)){
    StartFire ();
}
if(TempA>=(temper1+1)){
     StopFire ();
}
}
if(H11>=timeh2&&H11<timeh3){
if(TempA<=(temper2-1)){
StartFire ();
}
if(TempA>=(temper2+1)){
     StopFire ();
}
}

if(H11>=timeh3&&H11<timeh4){
if(TempA<=(temper3-1)){
StartFire ();
}
if(TempA>=temper3+1){
     StopFire ();
}

}
if(H11>=timeh4||H11<timeh1){
if(TempA<=temper4-1){
StartFire ();
}
if(TempA>=temper4+1){
  StopFire ();
}


}

Serial.print("Time_F:"); 
Serial.print(timeh1);
Serial.print("-"); 
Serial.print(timeh2);
Serial.print("-"); 
Serial.print(timeh3);
Serial.print("-"); 
Serial.println(timeh4);

Serial.print("Temp_F:"); 
Serial.print(temper1);
Serial.print("-"); 
Serial.print(temper2);
Serial.print("-"); 
Serial.print(temper3);
Serial.print("-"); 
Serial.println(temper4);
Serial.println("");
  }


 delay(1000); 
}


