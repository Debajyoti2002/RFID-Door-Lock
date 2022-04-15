#include <SPI.h>
#include <Servo.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
Servo servo1;
int servoPin = 6;
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  servo1.attach(servoPin);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "64 E5 CB 33") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Debajyoti. ACCEPTED!!");
    Serial.println();
    servo1.write(180);
    delay(3000);
    servo1.write(0);
  }
  else if(content.substring(1) == "F3 19 95 4F") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Rohan. ACCEPTED!!");
    Serial.println();
    servo1.write(180);
    delay(3000);
    servo1.write(0);
  }
  else if(content.substring(1) == "D3 5C 93 4F") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Adarsh. ACCEPTED!!");
    Serial.println();
    servo1.write(180);
    delay(3000);
    servo1.write(0);
  }
 else   {
    Serial.println(" Access denied");
    delay(3000);
  }
  servo1.write(180);
  delay(1000);
} 
