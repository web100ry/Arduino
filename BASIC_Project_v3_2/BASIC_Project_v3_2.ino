// Modified TFT_paint sketch from Adafruit_TFTLCD Library for
// TFT shield LCD 2.4" Chip ILI9341
// http://www.electronicavm.net
// @iPadNanito

#include <Adafruit_GFX.h>    // Libreria de graficos
#include <Adafruit_TFTLCD.h> // Libreria de LCD 
#include <TouchScreen.h>     // Libreria del panel tactil

#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 8   // can be a digital pin
#define XP 9   // can be a digital pin
// Definimos la presion máxima y minima que podemos realizar sobre el panel
#define MINPRESSURE 1
#define MAXPRESSURE 1000

// Para mejor precision de la presion realizada, es necesario 
// medir la resistencia entre los pines X+ y X-.
// En Shield TFT 2.4" LCD se mide entre los pines A2 y 6
// Instancia del panel tactil (Pin XP, YP, XM, YM, Resistencia del panel) 
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 364); 

short TS_MINX = 218; // Coordenadas del panel tactil para delimitar
short TS_MINY = 847; // el tamaño de la zona donde podemos presionar
short TS_MAXX = 949; // y que coincida con el tamaño del LCD
short TS_MAXY = 86; 

#define LCD_CS A3   // Definimos los pines del LCD
#define LCD_CD A2   // para poder visualizar elementos graficos
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

#define  BLACK   0x0000  // Definimos los colores 
#define BLUE    0x001F  // que utilizaremos para 
#define RED     0xF800  // el texto y los elementos graficos
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET); // Instancia LCD 

int X; // Variables que almacenaran la coordenada
int Y; // X, Y donde presionemos y la variable Z 
int Z; // almacenara la presion realizada

int a = 0; // variable "flag" para control rebotes
int aa = 0; // variable "flag" para control rebotes
int b = 0; // variable "flag" para control rebotes
int bb = 0; // variable "flag" para control rebotes
#define ledA 5
#define ledK 3

void setup(void) 
{ 
  tft.begin(0x9341); // Iniciamos el LCD especificando el controlador ILI9341. 
  
  tft.fillScreen(CYAN); // Pintamos la pantalla de Rojo

  pinMode(13, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  
  tft.drawRect(40, 20, 160, 60, RED); // Dibujamos un "boton"
 
  tft.setCursor(50,35);  // Colocamos el cursor
  tft.setTextSize(4);    // Especificamos el tamaño del texto
  tft.setTextColor(RED); // Definimos el color del texto 
  tft.println("BOTON1"); // Escribimos por pantalla     

tft.drawRect(40, 90, 160, 60, RED); // Dibujamos un "boton"
  
  tft.setCursor(50,105);  // Colocamos el cursor
  tft.setTextSize(4);    // Especificamos el tamaño del texto
  tft.setTextColor(RED); // Definimos el color del texto 
  tft.println("BOTON2"); // Escribimos por pantalla     


  
}

void loop()
{          
    lecturaPanel(); // Realizamos lectura del panel para detectar presion y coordenadas
      
    // Si la pulsación del eje X se produce entre los puntos 40 y 160
    // Y la pulsacion del eje Y se produce entre los puntos 20 y 60
    // Y la presión realizada esta entre el margen determinado
    if((X > 40 && X < 200) && (Y > 180 && Y < 240) && (Z > MINPRESSURE && Z < MAXPRESSURE)) 
    {
      if (a == 0) // Si la variable flag esta en 0
      {
        tft.fillRect(40, 20, 160, 60, RED); // Dibujamos nuestro boton relleno de color
        
        tft.setCursor(50,25); // Colocamos el cursor
        tft.setTextSize(3);   // Especificamos el tamaño del texto
        tft.setTextColor(WHITE); // Definimos el color del texto 
        tft.println("BOTON1"); // Escribimos por pantalla
        tft.setCursor(50,50);  // Colocamos el cursor
        tft.println("PULSADO1"); // Escribimos por pantalla   

tft.setCursor(210,45);  // Colocamos el cursor
  tft.setTextSize(2);    // Especificamos el tamaño del texto
  tft.setTextColor(RED); // Definimos el color del texto 
  tft.println(aa++); // Escribimos por pantalla     

    
        digitalWrite(ledA, HIGH);
       digitalWrite(ledK, LOW);

        a = 1; // Ponemos la variable flag en 1
           digitalWrite(13, HIGH);
        delay(150);
  
  
      }
      else if (a == 1) // Si la variable flag esta en 1
      {
         tft.fillRect(41, 21, 158, 58, CYAN); // Dibujamos el fondo de nuestro boton en cyan
         
         tft.setCursor(50,35); // Colocamos el cursor
         tft.setTextSize(4); // Especificamos el tamaño del texto
         tft.setTextColor(RED); // Definimos el color del texto 
         tft.println("BOTON1"); // Escribimos por pantalla

tft.setCursor(210,45);  // Colocamos el cursor
  tft.setTextSize(2);    // Especificamos el tamaño del texto
  tft.setTextColor(CYAN); // Definimos el color del texto 
  tft.println(aa-1); // Escribimos por pantalla  
         
        digitalWrite(ledA, LOW);
        digitalWrite(ledK, LOW);
         
         a = 0; // Ponemos la variable flag en 0 para evitar los rebotes
            digitalWrite(13, LOW);
         delay(150);
      }
    }    




//-------------------------------------------------------------------------------------

if((X > 40 && X < 200) && (Y > 120 && Y < 160) && (Z > MINPRESSURE && Z < MAXPRESSURE)) 
    {
      if (b == 0) // Si la variable flag esta en 0
      {
        tft.fillRect(40, 90, 160, 60, RED); // Dibujamos nuestro boton relleno de color
        
        tft.setCursor(50,95); // Colocamos el cursor
        tft.setTextSize(3);   // Especificamos el tamaño del texto
        tft.setTextColor(WHITE); // Definimos el color del texto 
        tft.println("BOTON2"); // Escribimos por pantalla
        tft.setCursor(50,122);  // Colocamos el cursor
        tft.println("PULSADO2"); // Escribimos por pantalla   
      
      tft.setCursor(210,110);  // Colocamos el cursor
  tft.setTextSize(2);    // Especificamos el tamaño del texto
  tft.setTextColor(RED); // Definimos el color del texto 
  tft.println(bb++); // Escribimos por pantalla  
      
       //digitalWrite(13, LOW);
        digitalWrite(ledA, HIGH);
       digitalWrite(ledK, LOW);

        b = 1; // Ponemos la variable flag en 1
        digitalWrite(13, HIGH);
        delay(150);
      }
      else if (b == 1) // Si la variable flag esta en 1
      {
         tft.fillRect(41, 91, 158, 58, CYAN); // Dibujamos el fondo de nuestro boton en cyan
         
         tft.setCursor(50,105); // Colocamos el cursor
         tft.setTextSize(4); // Especificamos el tamaño del texto
         tft.setTextColor(RED); // Definimos el color del texto 
         tft.println("BOTON2"); // Escribimos por pantalla
        
         tft.setCursor(210,110);  // Colocamos el cursor
  tft.setTextSize(2);    // Especificamos el tamaño del texto
  tft.setTextColor(CYAN); // Definimos el color del texto 
  tft.println(bb-1); // Escribimos por pantalla  
        digitalWrite(ledA, LOW);
        digitalWrite(ledK, LOW);
         
         b = 0; // Ponemos la variable flag en 0 para evitar los rebotes
            digitalWrite(13, LOW);
         delay(150);
      }
    }    




//-------------------------------------------------------------------------------------






    
}

void lecturaPanel()
{
    //digitalWrite(13, HIGH); 
    TSPoint p = ts.getPoint(); // Realizamos lectura de las coordenadas
  
  
    pinMode(XM, OUTPUT); // La librería utiliza estos pines como entrada y salida
    pinMode(YP, OUTPUT); // por lo que es necesario declararlos como salida justo
                         // despues de realizar una lectura de coordenadas.    
  
    // Mapeamos los valores analogicos leidos del panel tactil (0-1023)
    // y los convertimos en valor correspondiente a la medida del LCD 320x240
    X = map(p.y, TS_MAXX,TS_MINX, tft.width(), 0);
    Y = map(p.x, TS_MAXY, TS_MINY, tft.height(), 0);
    Z = p.z;
}
