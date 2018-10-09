/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x32 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

int potPin = 2;    // select the input pin for the potentiometer
int val = 0;       // variable to store the value coming from the sensor

int emfA = A0;
int emfB = A1;
int emfC = A2;
int A_HI = 0;
int A_LOW = 0;
int B_HI = 0;
int B_LOW = 0;
int C_HI = 0;
int C_LOW = 0;

void setup()   {                
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();

  // text display tests
  display.setTextSize(2);
  display.setTextColor(WHITE);  
  
  pinMode(A_HI,OUTPUT);
  pinMode(A_LOW,OUTPUT);
  pinMode(B_HI,OUTPUT);
  pinMode(B_LOW,OUTPUT);
  pinMode(C_HI,OUTPUT);
  pinMode(C_LOW,OUTPUT);
}

void loop() {
  val = analogRead(potPin);    // read the value from the potentiometer
  Delay=map(t,0,1024,1,1000); //we obtain the delay speed using the potentiometer
  //we map the values from 1 to 1000 microseaconds
  display.clearDisplay();
  display.setCursor(0,0);
  display.println(val);
  display.display();
  delay(500);
      
      
  int emA = analogRead(emfA);
  int emB = analogRead(emfB);
  int emC = analogRead(emfC);
  int sum = (emA+emB+emC)/3;  

  unsigned long currentMillis = micros();
 
  
  if(currentMillis - previousMillis >= Delay)
  {
    previousMillis += Delay;
    switch(fase)
    {
    //Phase1 C-B
      case 1:
        break;
    //Phase2 A-B
      case 2:
        break;
    //Phase3 A-C
      case 3: 
        break;   
    //Phase4 B-C
      case 4:
        break;
    //Phase5 B-A 
      case 5:
        break;
    //Phase6 C-A
      case 6:
        break;
    }
  
    if (Lastdelta < 0)
    {
      if (delta > 0)
      {
        Lastdelta=delta; //save the last delta
        fase= fase + 1;
        if (fase > 6) 
        {
          fase = 1;
        }
      }
    }//Zero cross from - to +  
    
    if (Lastdelta > 0)
    {
      if (delta < 0)
      {
        Lastdelta=delta;
        fase= fase + 1;
        if (fase > 6) 
        {
          fase = 1;
        }
      }
    }//Zero cross from + to - 
  }//Case ends
}

void PhaseCB()
{
  digitalWrite(AA1,LOW);
  digitalWrite(AA2,LOW);
  digitalWrite(BB1,LOW);
  digitalWrite(CC2,LOW);
  digitalWrite(BB2,HIGH);
  digitalWrite(CC1,HIGH);
  delta = emA-sum;
}

void PhaseCA()
{
  digitalWrite(AA1,LOW);
  digitalWrite(BB1,LOW);
  digitalWrite(BB2,LOW);
  digitalWrite(CC2,LOW);
  digitalWrite(CC1,HIGH);
  digitalWrite(AA2,HIGH);
  delta = emB-sum;
}

void PhaseBA()
{
  digitalWrite(AA1,LOW);
  digitalWrite(BB2,LOW);
  digitalWrite(CC1,LOW);
  digitalWrite(CC2,LOW);
  digitalWrite(AA2,HIGH);
  digitalWrite(BB1,HIGH);
  delta = emC-sum;
}

void PhaseBC()
{
  digitalWrite(AA1,LOW);
  digitalWrite(AA2,LOW);
  digitalWrite(BB2,LOW);
  digitalWrite(CC1,LOW);
  digitalWrite(BB1,HIGH);
  digitalWrite(CC2,HIGH);
  delta = emA-sum;
}

void AB()
{
  digitalWrite(AA2,LOW);
  digitalWrite(BB1,LOW);
  digitalWrite(CC1,LOW);
  digitalWrite(CC2,LOW);
  digitalWrite(AA1,HIGH);
  digitalWrite(BB2,HIGH);
  delta = emC-sum;
}

void PhaseAC()
{
  digitalWrite(AA2,LOW);
  digitalWrite(BB1,LOW);
  digitalWrite(BB2,LOW);
  digitalWrite(CC1,LOW);
  digitalWrite(CC2,HIGH);
  digitalWrite(AA1,HIGH);
  delta = emB-sum;
}

