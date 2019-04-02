#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
bool test(const char input[4]){
  char master[] = ")⸮V⸮";
  for(int i=0; i<4; i++){
    char tmp = input[i];
    Serial.println(tmp);
    if(master[i] != tmp){
      Serial.println("FAILED ON: " + tmp);
      return false;
    }
  }
  return true;
}
void setup() {
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
}

void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  // Dump debug info about the card; PICC_HaltA() is automatically called
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

  char input[4];
  for(int i =0; i<4; i++){
    char tmp =char(mfrc522.uid.uidByte[i]);
    Serial.print(i);
    Serial.print(" ");
    Serial.println(tmp);
    input[i] = tmp;
  }

  if(test(input) == true){
    digitalWrite(7, HIGH);
    digitalWrite(6, LOW);
  }
  else{
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
  }
  Serial.println();
  
}
