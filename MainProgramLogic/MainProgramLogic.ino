



/*
   Constants: Created because the actual permanent memory is small
*/
#include <Wire.h>
#include <SPI.h>
#include <Servo.h>
#include <MFRC522.h> //figure out what these should be later
#include <LiquidCrystal_I2C.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

MFRC522 reader(SS_PIN, RST_PIN);   // Create MFRC522 instance
LiquidCrystal_I2C lcd(0x27, 16, 1); // Create LCD display address, columns, rows

char MEDICATION1 = "Mini M&M";
char MEDICATION2 = "Robin's Egg";

int MEDICATION1_TO_DISPENSE = 1;
int MEDICATION2_TO_DISPENSE = 2;

char USER1_NAME = "Tim";
char USER2_NAME = "SwagDaddi3000";

bool u1_canTakeM1 = true;
bool u2_canTakeM1 = false;
bool u1_canTakeM2 = true;
bool u2_canTakeM2 = true;

int SERVO_ROTATE = 90;
int SERVO_1_PIN = 5;
int SERVO_2_PIN = 6;
int BACK_BUTTON_PIN = 2;
int FORWARD_BUTTON_PIN = 3;
int SELECT_BUTTON_PIN = 4;
int backButton = 0;
int frontButton = 0;
int selectButton = 0;

Servo servo1;
Servo servo2;
int userNum = -1;
bool known = false, unknown = false;
short int c = 0;


void setup() {
  servo1.attach(SERVO_1_PIN);
  servo2.attach(SERVO_2_PIN);
  servo2.write(0);
  pinMode(BACK_BUTTON_PIN, INPUT);
  pinMode(FORWARD_BUTTON_PIN, INPUT);
  pinMode(SELECT_BUTTON_PIN, INPUT);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);   // Initialize serial communications with the PC
  SPI.begin();      // Init SPI bus
  reader.PCD_Init();   // Init Card Reader
  reader.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  lcd.print("Please Scan Card");
}

void displayMed(char medName) {
  lcd.print("MEDHERE");
}

void greetUser(char userName) {
  char line = "WELCOME:" + userName;
  lcd.print("WELCOMEHERE");
  delay(2000); //delay for 2s so user can read
  lcd.clear();
}

void auth(MFRC522 reader) { //authenticate user
  byte user1[4] = {0x29, 0xFB, 0x56, 0xD3};//The hexidecimal UID
  byte user2[4] = {0x76, 0x50, 0xB8, 0x1A};
  if (reader.uid.uidByte[0] == user1[0] && reader.uid.uidByte[1] == user1[1] && reader.uid.uidByte[2] == user1[2] && reader.uid.uidByte[3] == user1[3]) {
    userNum = 1;
  }
  else if (reader.uid.uidByte[0] == user2[0] && reader.uid.uidByte[1] == user2[1] && reader.uid.uidByte[2] == user2[2] && reader.uid.uidByte[3] == user2[3]) {
    userNum = 2;
  }
  else{
    userNum = -1;
  }
}

bool canTake(int medNum, int userNum) {
  Serial.println("CHECKTAKE");
  if (userNum == 1) {
    if (medNum == 1) {
      if (u1_canTakeM1) {
        return true;
      }
    } else {
      if (u1_canTakeM2) {
        return true;
      }
    }
  } else {
    if (medNum == 1) {
      if (u2_canTakeM1) {
        return true;
      }
    } else {
      if (u2_canTakeM2) {
        return true;
      }
    }
  }
  return false;
}

void dispense(int medNum) {
  Serial.println("DISPENSEWEEIHBUAHBAUHBD AEEDHB G");
  if (medNum == 1) {
    servo1.write(0);
    delay(800); //wait .8 second
    servo1.write(90);
  } else {
    servo2.write(SERVO_ROTATE);
    delay(1000);
    servo2.write(0);
  }
}

void dispenseMedicine(int medNum, int userNum) {
  if (canTake(medNum, userNum)) {
    lcd.clear();
    lcd.print("Dispensing...");
    dispense(medNum);
    //lcd.clear();
  }
  else {
    lcd.clear();
    lcd.print("You cannot take that now.");
    delay(2000); //pause for 2 seconds
    //lcd.clear();
  }
}

bool pressed = false;
int medNum = 0;

void loop() {
  c++;
  if (c >= 100000) { // a time out event
      c = 0;
      userNum = -1;
      pressed = false;
      lcd.clear();
      lcd.print("Please Scan Card");
    }
  if (userNum == -1) {
    if ( ! reader.PICC_IsNewCardPresent()) {// Look for new cards
      return;
    }
    // Select one of the cards
    if ( ! reader.PICC_ReadCardSerial()) {// Cant read
      return;
    }
      //reader.PICC_DumpToSerial(&(reader.uid));
      
    auth(reader);
    if (userNum = 1) { //checks which user swiped
      Serial.println("TRUE");
      lcd.clear();
      lcd.print("Hello: Tim");
      c = 0;
    } else if(userNum = 2) {
      Serial.println("User2");
      lcd.clear();
      lcd.print("Hello:SwagDaddi3000");
      c = 0;
    }
    
  }
  else {
    if (!pressed) {
      lcd.write("<- Select Med ->");
      if (medNum == 1) {
        lcd.write(MEDICATION1);
      } else if (medNum == 2) {
        lcd.write(MEDICATION2);
      }
    }
    
    backButton = digitalRead(BACK_BUTTON_PIN);
    frontButton = digitalRead(FORWARD_BUTTON_PIN);
    selectButton = digitalRead(SELECT_BUTTON_PIN);
    
    if (frontButton == HIGH) {
      medNum = 2;
      dispenseMedicine(userNum,medNum);
      pressed = true;
      lcd.clear();
    } else if (backButton == HIGH) {
      medNum = 1;
      dispenseMedicine(userNum,medNum);
      pressed = true;
      lcd.clear();
    }
  }
}
