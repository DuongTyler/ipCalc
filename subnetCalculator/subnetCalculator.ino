#include <LiquidCrystal.h>
// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
//Variables
int screenID = 0;
int cursorPos[2]={0,0};
byte arrowU[8] = {  //custom LCD character arrow
  B00000,
  B00100,
  B01110,
  B10101,
  B00100,
  B00100,
  B00100,
  B00100
};
int IPv4[4] = {192,/*.*/168,/*.*/002,/*.*/001};
int subnet[4] = { 255, 255, 255, 255 };
int lcd_key     = 0;
int adc_key_in  = 0;  //default button before read
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

// CONTROLS
int read_LCD_buttons()
{
  adc_key_in = analogRead(0);      // read the value from the sensor 
  // buttons when read are centered at these valies: 0, 144, 329, 504, 741
  if (adc_key_in > 1000) return btnNONE; 
  if (adc_key_in < 50)   return btnRIGHT;  
  if (adc_key_in < 195)  return btnUP; 
  if (adc_key_in < 380)  return btnDOWN; 
  if (adc_key_in < 555)  return btnLEFT; 
  if (adc_key_in < 790)  return btnSELECT;   

  return btnNONE;               // when all others fail, return this...
}

int updateLCD(String input, int x = 0, int y = 0)
{
  //lcd.clear();
  lcd.setCursor(x,y);
  lcd.print(input);
  return 0;
}
void calcIPv4()
{
  lcd.clear();
  updateLCD("Subnet:", 0, 1);
  bool t = false;
  for (int i = 0; i < 4; i ++)
  {
    lcd.setCursor(i*4,0);
        //to put a space before the subnet so that it does not start with a .
    if (t == false)
    {
      lcd.print(" "+String(subnet[i]));
      t=true;
    }
    else
    {
      lcd.print("."+String(subnet[i]));
    }
  }
  bool comp = false;
  lcd.setCursor(0,0);
  lcd.cursor();
  //lcd.blink();
  while(comp == false)
  {//####################SUBNET#######################################################################
    delay(300);
    lcd.setCursor(cursorPos[0], cursorPos[1]);
    lcd_key = read_LCD_buttons();
     
    switch (lcd_key)
    {
      case btnLEFT:
        cursorPos[0]--;
        break;
      case btnRIGHT:
        cursorPos [0] ++;
        break;
      case btnUP:
        //if (cursorPos[0] >= 
         if(cursorPos[0] <=3 && cursorPos[0] !=0)
              {
                  subnet[0]++;
              }
              if(cursorPos[0] >=5 && cursorPos[0] <=7)
              {
                  subnet[1]++;
              } 
              if(cursorPos[0] >=9 && cursorPos[0] <=11)
              {
                  subnet[2]++;
              }
               if(cursorPos[0] >=13 && cursorPos[0] <=15)
              {
                  subnet[3]++;
              }
               t = false;
                for (int i = 0; i < 4; i ++)
              {
                lcd.setCursor(i*4,0);
                    //to put a space before the subnet so that it does not start with a .
                if (t == false)
                {
                  lcd.print(" "+String(subnet[i]));
                  t=true;
                }
                else
                {
                  lcd.print("."+String(subnet[i]));
                }
              }
        break;
      case btnDOWN:
          t = false;
         if(cursorPos[0] <=3 && cursorPos[0] !=0)
              {
                  subnet[0]--;
              }
              if(cursorPos[0] >=5 && cursorPos[0] <=7)
              {
                  subnet[1]--;
              } 
              if(cursorPos[0] >=9 && cursorPos[0] <=11)
              {
                  subnet[2]--;
              }
               if(cursorPos[0] >=13 && cursorPos[0] <=15)
              {
                  subnet[3]--;
              }
              for (int i = 0; i < 4; i ++)
              {
                lcd.setCursor(i*4,0);
                    //to put a space before the subnet so that it does not start with a .
                if (t == false)
                {
                  lcd.print(" "+String(subnet[i]));
                  t=true;
                }
                else
                {
                  lcd.print("."+String(subnet[i]));
                }
              }
        break;
      case btnSELECT:
        comp = true;
        break;
      
    }
  }
  
}
void calcScrn()                   //Updates the calculator screen
{
  delay(100);
//  lcd.setCursor(0,1);
  lcd.write(byte(0));
  bool t = false;
  for (int i = 0; i < 4; i ++)
  {
    lcd.setCursor(i*4,0);
        //to put a space before the IP so that it does not start with a .
    if (t == false)
    {
      lcd.print(" "+String(IPv4[i]));
      t=true;
    }
    else
    {
      lcd.print("."+String(IPv4[i]));
    }
  }
  /*for (int i = 0; i < 15; i ++)
  {
    switch (i)
    {
      default:
        updateLCD(String(IPv4[i]),i,0);
        break;
    }
  }*/
}



void setup()
{
 lcd.begin(16, 2);              // start the library
 lcd.createChar(0,arrowU);      //use   lcd.write(byte(0));
 lcd.clear();
 lcd.cursor();
 lcd.blink();
}

void loop()
{
  lcd_key = read_LCD_buttons();
//  while(btnNONE)
//  {
//  }
  switch (screenID)
  {
    //HOME SCREEN ###########################################################################################
    case 0:
      updateLCD("IP calculator v1.1",5);
      updateLCD("Created by Tyler Duong - p5 APCSP", 0, 1);
      lcd.scrollDisplayLeft();
      delay(300);
      switch(lcd_key)
        {
            case btnSELECT:
              lcd.clear();
              delay(500);
              screenID = 1;
              break;
        }
      break;
    //CALCULATOR SCREEN #####################################################################################
    case 1:
      calcScrn();
      //sets cursor to default position
      lcd.setCursor(cursorPos[0],cursorPos[1]);
      
      switch(lcd_key)
        {
            case btnSELECT:
              calcIPv4();
              updateLCD("Calculating Net", 0, 1);
              break;
            case btnRIGHT:
              //lcd.scrollDisplayLeft();
              //Positive X direction for cursor
              cursorPos[0]++;
              if (cursorPos[0] > 15 )
              {
                cursorPos[0] = 15;
              }
              delay(100);
              break;
            case btnLEFT:
              //lcd.scrollDisplayRight();
              //Update X in negative direction for cursor
              cursorPos[0]--;
              if (cursorPos[0] < 0 )
              {
                cursorPos[0] = 0;
              }
              delay(100);
              break;
            case btnUP:
              //######################Updates IP numbers on screen index ##################################################
              if(cursorPos[0] <=3 && cursorPos[0] !=0)
              {
                  IPv4[0]++;
              }
              if(cursorPos[0] >=5 && cursorPos[0] <=7)
              {
                  IPv4[1]++;
              } 
              if(cursorPos[0] >=9 && cursorPos[0] <=11)
              {
                  IPv4[2]++;
              }
               if(cursorPos[0] >=13 && cursorPos[0] <=15)
              {
                  IPv4[3]++;
              }
              //END ####################################################################################################
              break;
           case btnDOWN:
              //######################Updates IP numbers on screen index ##################################################
              if(cursorPos[0] <=3 && cursorPos[0] !=0)
              {
                if(IPv4[0]!=0)
                {
                  IPv4[0]--;
                }
              }
              if(cursorPos[0] >=5 && cursorPos[0] <=8)
              {
                if(IPv4[1]!=0)
                {
                  IPv4[1]--;
                }
              } 
              if(cursorPos[0] >=9 && cursorPos[0] <=11)
              {
                if(IPv4[2]!=0)
                {
                  IPv4[2]--;
                }
              }
               if(cursorPos[0] >=13 && cursorPos[0] <=15)
              {
                if(IPv4[3]!=0)
                {
                  IPv4[3]--;
                }
              }
              //END ###################################################################################################
              break;
              
        }
      break;
  }
}
