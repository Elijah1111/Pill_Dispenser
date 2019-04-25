#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

MFRC522 reader(SS_PIN, RST_PIN);   // Create MFRC522 instance
LiquidCrystal_I2C lcd(0x27, 16, 1); // Create LCD display address, columns, rows


bool auth(MFRC522 reader) { //authenticate user

  byte master[4] = {0x29, 0xFB, 0x56, 0xD3};//The hexidecimal UID
  if (   reader.uid.uidByte[0] == master[0] &&
         reader.uid.uidByte[1] == master[1] &&
         reader.uid.uidByte[2] == master[2] &&
         reader.uid.uidByte[3] == master[3]   ) {
    return true;
  }
  return false;

}


void setup() {
  Serial.begin(9600);   // Initialize serial communications with the PC
  lcd.init();
  lcd.backlight();
  SPI.begin();      // Init SPI bus
  reader.PCD_Init();   // Init Card Reader
  reader.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  lcd.print("Please Scan Card");
}
bool known = false, unknown = false;
short int c = 0;
void loop() {
  
  c++;
  if (c >= 500) { // a time out event
    c = 0;
    unknown = false;
    known = false;
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);
    lcd.clear();
    lcd.print("Please Scan Card");
    return;
  }
  if ( ! reader.PICC_IsNewCardPresent()) {// Look for new cards
    return;
  }
  // Select one of the cards
  if ( ! reader.PICC_ReadCardSerial()) {// Cant read
    return;
  }

  if (auth(reader)) {
  if (!known) { //checks to see if the input id is the stored user
      Serial.println("TRUE");
      lcd.clear();
      lcd.print("WELCOME: M Bison");
      known = true;
      unknown = false;
      c = 0;
    }
  }
  else if (!unknown) {
  Serial.println("FALSE");
    lcd.clear();
    lcd.print("ACCESS DENIED");
    unknown = true;
    known = false;
    c = 0;
  }

}
