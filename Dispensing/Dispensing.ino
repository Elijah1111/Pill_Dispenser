#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

MFRC522 reader(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  reader.PCD_Init();   // Init MFRC522
  reader.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
}

void loop() {
  // Look for new cards
  if ( ! reader.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if ( ! reader.PICC_ReadCardSerial()) {
    return;
  }
  // Dump debug info about the card; PICC_HaltA() is automatically called
  //reader.PICC_DumpToSerial(&(reader.uid));

  byte input[4];
  for(int i =0; i<4; i++){
    byte tmp = reader.uid.uidByte[i];
    Serial.print(i);
    Serial.print(" ");
    Serial.println(tmp);
    input[i] = tmp;
  }
byte master[4] = {0x29, 0xFB, 0x56, 0xD3};

  if(reader.uid.uidByte[0] == master[0] && 
     reader.uid.uidByte[1] == master[1] &&
     reader.uid.uidByte[2] == master[2] &&
     reader.uid.uidByte[3] == master[3]){//checks to see if the input id is the stored user
    Serial.println("TRUE");
    digitalWrite(7, HIGH);
    digitalWrite(6, LOW);
  }
  else{
    Serial.println("FALSE");
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
  }
  Serial.println();
  
}
