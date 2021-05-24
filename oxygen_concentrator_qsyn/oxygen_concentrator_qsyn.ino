
// Quarantined Student Youth Network 
// Oxygen Concentrator for the people
// Code by Arijit Shaw

#include <LiquidCrystal.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;
LiquidCrystal lcd = LiquidCrystal(7,6,5,4,3,2);

int L_in = 13; //Defined Pin as Variable
int R_in = 12; //Defined Pin as Variable
int L_N2 = 11; //Defined Pin as Variable
int R_N2 = 10; //Defined Pin as Variable
int L_out = 9;
int R_out = 8;

int T[6][6] = {{1,0,0,1,1,0},
         {1,0,0,1,1,1},
         {1,1,0,0,1,1},
         {0,1,1,0,0,1},
         {0,1,1,0,1,1},
         {1,1,0,0,1,1}};

int delays[] = {4000,450,700,4000,450,700}; // Production_Delay, Flush_Delay, PreCharge_Delay

int16_t adc0;

void setup()
{
  Serial.begin(9600);

  lcd.begin(16, 2);
  ads.begin();
  
  pinMode(L_in, OUTPUT);
  pinMode(R_in, OUTPUT);
  pinMode(L_N2, OUTPUT);
  pinMode(R_N2, OUTPUT);
  pinMode(L_out, OUTPUT);
  pinMode(R_out, OUTPUT);

}

void checkPurity()
{
  adc0 = ads.readADC_SingleEnded(0);
  lcd.setCursor(0, 0);
  lcd.print("Q S Y N  & E F A");
  lcd.setCursor(0, 1);
  lcd.print("Purity = ");
  lcd.setCursor(9, 1);
  lcd.print(adc0*0.02625);
  lcd.setCursor(14, 1);
  lcd.print(" %");  
}

void createDelay(int delaytime)
{
  while(delaytime >= 1000)
  {
    checkPurity();
    delaytime -= 1000;
    delay(1000);
  }
  
  if (delaytime > 0)
    delay(delaytime);

}

void loop()
{
  for (int cycle = 0; cycle < 6; cycle++) {
    digitalWrite(L_in, T[cycle][0]);
    digitalWrite(R_in, T[cycle][1]);
    digitalWrite(L_N2, T[cycle][2]);
    digitalWrite(R_N2, T[cycle][3]);
    digitalWrite(L_out, T[cycle][4]);
    digitalWrite(R_out, T[cycle][5]);
    createDelay(delays[cycle]);
  }
}
