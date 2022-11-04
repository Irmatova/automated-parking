#include <Stepper.h>
#include <TM1638.h> //8tali button
#include "SPI.h"     //RFID uchun
#include "MFRC522.h" //RFID uchun
#define SS_PIN 53    //RFID uchun, MOSI=51, MISO=50, SCK=52
#define RST_PIN 5    //RFID uchun
#define PIN_trig 11 //trip portini ulanish raqami
#define PIN_echo 10

TM1638 module(7, 6, 4);//data pin 7, clock pin 6, strobe pin 4
double qadam = 2048;
long duration, sm;
Stepper eshik(qadam, 41, 45, 43, 47);
Stepper disk(qadam, 40,44,42,46);
Stepper Charxpalak(qadam, 23,27,25,29);
int val;
int top= 12, house=8, street = 9;
boolean cab1=false, cab2=false, cab3=false, cab4=false, cab5=false, cab6=false, cab7=false, cab8=false;
int c1=0, c2=0, c3=0, c4=0, c5=0, c6=0, c7=0, c8=0;
MFRC522 rfid(SS_PIN, RST_PIN);//RFID uchun
MFRC522::MIFARE_Key key;//RFID uchun

void setup()
{
  eshik.setSpeed(10);
  disk.setSpeed(10);
  Charxpalak.setSpeed(10);
  Serial.begin(9600);
  SPI.begin();  //RFID uchun
  rfid.PCD_Init();//RFID UCHUN
  pinMode(top, OUTPUT);
  pinMode(house, OUTPUT);
   pinMode(street, OUTPUT);
 
  
   // display a hexadecimal number and set the left 4 dots
  module.setDisplayToHexNumber(0x12345678, 0x00);
   pinMode(PIN_trig,OUTPUT); 
  pinMode(PIN_echo, INPUT);
}
void loop()
{   //masofa moduli
  digitalWrite(PIN_trig,LOW);
  delay(1000);
  digitalWrite(PIN_trig, HIGH); //birinchi kichkina impul jo'natamiz, 40kHz chastota bn

  delay(1000);
  digitalWrite(PIN_trig,LOW);
  duration = pulseIn(PIN_echo, HIGH); //exolakatordagi ovozni tutilish vaqtini aniqlash
  sm = (duration / 2)/ 29.1; //aniqlangan vaqt orqali masofani aniqlash
  if(sm<11)
  {
     eshik.step(3000);
     delay(3000);
     Charxpalak.step(6240);
     delay(3000);
     eshik.step(-3000);
     delay(3000);
     Charxpalak.step(-6240);      
     cab8=true;
        
   }  
  //Mobil boshqaruv
  if (Serial.available())
  {
    val = Serial.read();
    if ((val == 'l')||(val == 'm'))
    {
       digitalWrite(top,1);
    }
    if ((val == 'r')||(val == 's'))
    {
       digitalWrite(top,0);
    }
    if (val == 'n')
    {
       digitalWrite(house,1);
    }
     if (val == 't')
    {
       digitalWrite(house,0);
    }
    if (val == 'o')
    {
       digitalWrite(street,1);
    }
    if (val == 'u')
    {
       digitalWrite(street,0);
    }
    if (val == 'p')
    {
       digitalWrite(top,1);
       digitalWrite(house,1);
       digitalWrite(street,1);
    }
    if (val == 'v')
    {
       digitalWrite(top,0);
       digitalWrite(house,0);
       digitalWrite(street,0);
    }
    if (val == 'a')
    {
       eshik.step(3000);
      delay(3000);
    }
       if ( val == 'b')
    {
      eshik.step(-3000);
      delay(3000);
    }
   if (val == 'c')
    {
      disk.step(1024);
      delay(3000);
    }
       if ( val == 'q')
    {
      disk.step(-1024);
      delay(3000);
    }
    if (val == 'd')
    {
      delay(3000);
      eshik.step(3000);
      delay(3000);
      eshik.step(-3000);
      cab1=true;
    }
    if (val == '1')
    {
      delay(3000);
      eshik.step(3000);
      delay(3000);
    if(sm<20){ delay(3000);
      disk.step(1024);
      delay(3000);}
      eshik.step(-3000);
      delay(3000);
      cab1=false;
    }
     if (val == 'e')
    {
      Charxpalak.step(1560);
        delay(3000);
        eshik.step(3000);
        delay(3000);
        eshik.step(-3000);
        delay(3000);
        Charxpalak.step(-1560);      
        cab2=true;
    }
      if (val == '2')
    {
      Charxpalak.step(1560);
        delay(3000);
        eshik.step(3000);
        delay(3000);
       if(sm<20){ delay(3000);
      disk.step(1024);
      delay(3000);}
      eshik.step(-3000);
        delay(3000);
         Charxpalak.step(-1560);      
        cab2=false;
    }
       if ( val == 'f')
    {
       Charxpalak.step(2340);
        delay(3000);
        eshik.step(3000);
        delay(3000);
        eshik.step(-3000);
        delay(3000);
        Charxpalak.step(-2340);      
        cab3=true;
    }
    if ( val == '3')
    {
       Charxpalak.step(2340);
        delay(3000);
        eshik.step(3000);
        delay(3000);
       if(sm<20){ delay(3000);
      disk.step(1024);
      delay(3000);}
       eshik.step(-3000);
        delay(3000);
        Charxpalak.step(-2340);      
        cab3=false;
    }
     if (val == 'g')
    {
      Charxpalak.step(3120);
        delay(3000);
        eshik.step(3000);
        delay(3000);
        eshik.step(-3000);
        delay(1000);
        Charxpalak.step(-3120);      
        cab4=true;
    }
    if (val == '4')
    {
      Charxpalak.step(3120);
        delay(3000);
        eshik.step(3000);
        delay(3000);
        if(sm<20){ delay(3000);
      disk.step(1024);
      delay(3000);}
      eshik.step(-3000);
        delay(3000);
        Charxpalak.step(-3120);      
        cab4=false;
    }
       if ( val == 'h')
    {
      Charxpalak.step(3900);
        delay(3000);
        eshik.step(3000);
        delay(3000);
        eshik.step(-3000);
        delay(3000);
        Charxpalak.step(-3900);      
        cab5=true;
    }
    if ( val == '5')
    {
      Charxpalak.step(3900);
        delay(3000);
        eshik.step(3000);
        delay(3000);
        if(sm<20){ delay(3000);
      disk.step(1024);
      delay(3000);}
      eshik.step(-3000);
        delay(3000);
        Charxpalak.step(-3900);      
        cab5=false;
    }
     if (val == 'i')
    {
      Charxpalak.step(4680);
        delay(3000);
        eshik.step(3000);
        delay(3000);
        eshik.step(-3000);
        delay(3000);
        Charxpalak.step(-4680);      
        cab6=true;
    }
    if (val == '6')
    {
      Charxpalak.step(4680);
        delay(3000);
        eshik.step(3000);
        delay(3000);
        if(sm<20){ delay(3000);
      disk.step(1024);
      delay(3000);}
      eshik.step(-3000);
        delay(3000);
      Charxpalak.step(-4680);      
        cab6=false;
    }
    if (val == 'j')
    {
     Charxpalak.step(5460);
        delay(3000);
        eshik.step(3000);
        delay(3000);
        eshik.step(-3000);
        delay(3000);
        Charxpalak.step(-5460);      
        cab7=true;
    }
    if (val == '7')
    {
     Charxpalak.step(5460);
        delay(3000);
        eshik.step(3000);
        delay(3000);
       if(sm<20){ delay(3000);
      disk.step(1024);
      delay(3000);}
       eshik.step(-3000);
        delay(3000);
      Charxpalak.step(-5460);      
        cab7=false;
    }
     if (val == 'k')
    {
      Charxpalak.step(6240);
        delay(3000);
        eshik.step(3000);
        delay(3000);
        eshik.step(-3000);
        delay(3000);
        Charxpalak.step(-6240);      
        cab8=true;
    }
    if (val == '8')
    {
      Charxpalak.step(6240);
        delay(3000);
        eshik.step(3000);
        delay(5000);
      if(sm<20){ delay(3000);
      disk.step(1024);
      delay(3000);}
        eshik.step(-3000);
        delay(3000);
     Charxpalak.step(-6240);      
        cab8=false;
    }
  }
  
  //8 tali batton orqali boshqaruv
    byte keys = module.getButtons();
    if(keys==1)   
    { delay(3000);
      eshik.step(3000);
      delay(3000);
      eshik.step(-3000);
      cab1=true;
        c1++;
    } 
     if(c1==2)  //cab1 true bo'lsa
        {
         eshik.step(3000);
          delay(3000);
          eshik.step(-3000);
          cab1=false;
          c1=0;
          }               
    if(keys==2)   
    {   Charxpalak.step(1560);
        delay(3000);
        eshik.step(3000);
        delay(5000);
        eshik.step(-3000);
        delay(1000);
        Charxpalak.step(-1560);      
        cab2=true; c2++;
     }
     if(c2==2)     //cab2 true bo'lsa
     {  Charxpalak.step(1560);
        delay(3000);
        eshik.step(3000);
        delay(5000);
        if(sm<20){ delay(3000);
      disk.step(1024);
      delay(5000);}
        eshik.step(-3000);
        delay(1000);
        Charxpalak.step(-1560);
        cab2=false;   
        c2=0;       
          }
    if(keys==4)
    {  Charxpalak.step(2340);
        delay(3000);
        eshik.step(3000);
        delay(5000);
        eshik.step(-3000);
        delay(1000);
        Charxpalak.step(-2340);      
        cab3=true; c3++;
     }
     if(c3==2)      //cab3 true bo'lsa
     {  Charxpalak.step(2340);
        delay(3000);
        eshik.step(3000);
        delay(5000);
        if(sm<20){ delay(3000);
      disk.step(1024);
      delay(5000);}
        eshik.step(-3000);
        delay(1000);
        Charxpalak.step(-2340);
        cab3=false;   
        c3=0;       
      }
        if(keys==8)
    {  Charxpalak.step(3120);
        delay(3000);
        eshik.step(3000);
        delay(5000);
        eshik.step(-3000);
        delay(1000);
        Charxpalak.step(-3120);      
        cab4=true; c4++;
     }
     if(c4==2)       //cab4 true bo'lsa
     {  Charxpalak.step(3120);
        delay(3000);
        eshik.step(3000);
        delay(5000);
        if(sm<20){ delay(3000);
      disk.step(1024);
      delay(5000);}
        eshik.step(-3000);
        delay(1000);
        Charxpalak.step(-3120);
        cab4=false;   
        c4=0;       
      }
       if(keys==16)
    {  Charxpalak.step(3900);
        delay(3000);
        eshik.step(3000);
        delay(5000);
        eshik.step(-3000);
        delay(1000);
        Charxpalak.step(-3900);      
        cab5=true; c5++;
     }
     if(c5==2)    //cab5 true bo'lsa
     {  Charxpalak.step(3900);
        delay(3000);
        eshik.step(3000);
        delay(5000);
        if(sm<20){ delay(3000);
      disk.step(1024);
      delay(5000);}
        eshik.step(-3000);
        delay(1000);
        Charxpalak.step(-3900);
        cab5=false;   
        c5=0;       
      }
      if(keys==32)
    {  Charxpalak.step(4680);
        delay(3000);
        eshik.step(3000);
        delay(5000);
        eshik.step(-3000);
        delay(1000);
        Charxpalak.step(-4680);      
        cab6=true; c6++;
     }
     if(c6==2)    //cab6 true bo'lsa
     {  Charxpalak.step(4680);
        delay(3000);
        eshik.step(3000);
        delay(5000);
        if(sm<20){ delay(3000);
      disk.step(1024);
      delay(5000);}
        eshik.step(-3000);
        delay(1000);
        Charxpalak.step(-4680);
        cab6=false;   
        c6=0;       
      }
      if(keys==64)
    {  Charxpalak.step(5460);
        delay(3000);
        eshik.step(3000);
        delay(5000);
        eshik.step(-3000);
        delay(1000);
        Charxpalak.step(-5460);      
        cab7=true; c7++;
     }
     if(c7==2)
     {  Charxpalak.step(5460);
        delay(3000);
        eshik.step(3000);
        delay(5000);
        if(sm<20){ delay(3000);
      disk.step(1024);
      delay(5000);}
        eshik.step(-3000);
        delay(1000);
        Charxpalak.step(-5460);
        cab7=false;   
        c7=0;       
      }
      if(keys==128)
    {  Charxpalak.step(6240);
        delay(3000);
        eshik.step(3000);
        delay(5000);
        eshik.step(-3000);
        delay(1000);
        Charxpalak.step(-6240);      
        cab8=true; c8++;
     }
     if(c8==2)
     {  Charxpalak.step(6240);
        delay(3000);
        eshik.step(3000);
        delay(5000);
        if(sm<20){ delay(3000);
      disk.step(1024);
      delay(3000);}
        eshik.step(-3000);
        delay(1000);
        Charxpalak.step(-6240);
        cab8=false;   
        c8=0;       
      }
  //RFID orqali boshqaruv
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  // Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  // Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }
  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
      (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
      String(rfid.uid.uidByte[i], HEX) +
      (i != 3 ? ":" : "");
  }

  strID.toUpperCase();
  Serial.print("Kalitni tekkizing: ");
  Serial.println(strID);
  delay(1000);
 if (strID.indexOf("E0:8F:55:1F") >= 0) {  //put your own tap card key;
      Charxpalak.step(1560);
        delay(3000);
        eshik.step(3000);
        delay(5000);
        if(sm<20){ delay(3000);
      disk.step(1024);
      delay(5000);}
        eshik.step(-3000);
        delay(1000);
        Charxpalak.step(-1560);
        cab2=false; 
        return;
  }
   if (strID.indexOf("9A:C5:6B:1A") >= 0) {  //put your own tap card key;
      Charxpalak.step(2340);
        delay(3000);
        eshik.step(3000);
        delay(5000);
        if(sm<20){ delay(3000);
      disk.step(1024);
      delay(5000);}
        eshik.step(-3000);
        delay(1000);
        Charxpalak.step(-2340);
        cab3=false; 
        return;
  }
  if (strID.indexOf("9A:2E:5A:19") >= 0) {  //put your own tap card key;
      Charxpalak.step(3120);
        delay(3000);
        eshik.step(3000);
        delay(5000);
        if(sm<20){ delay(3000);
      disk.step(1024);
      delay(5000);}
        eshik.step(-3000);
        delay(1000);
        Charxpalak.step(-3120);
        cab4=false; 
        return;
  }
   if (strID.indexOf("05:80:3E:D1:BA:11:00") >= 0) {  //put your own tap card key;
      Charxpalak.step(3900);
        delay(3000);
        eshik.step(3000);
        delay(5000);
        if(sm<20){ delay(3000);
      disk.step(1024);
      delay(5000);}
        eshik.step(-3000);
        delay(1000);
        Charxpalak.step(-3900);
        cab5=false;
        return;
  }
 
}
