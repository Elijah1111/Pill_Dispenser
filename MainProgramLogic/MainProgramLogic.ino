

/*
 * Constants: Created because the actual permanent memory is small
 */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16, 1); // set the LCD address to 0x27 for a 16 chars and 2 line display
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

MFRC522 reader(SS_PIN, RST_PIN);   // Create MFRC522 instance
LiquidCrystal_I2C lcd(0x27, 16, 1); // Create LCD display address, columns, rows

string MEDICATION1 = "Mini M&M";
string MEDICATION2 = "Robin's Egg";

int MEDICATION1_TO_DISPENSE = 1;
int MEDICATION2_TO_DISPENSE = 2;

string USER1_NAME = "Tim";
string USER2_NAME = "SwagDaddi3000";

bool u1_canTakeM1 = true;
bool u2_canTakeM1 = false;
bool u1_canTakeM2 = true;
bool u2_canTakeM2 = true;

int SERVO_ROTATE = 90;
int SERVO_1_PIN;
int SERVO_2_PIN;
int BACK_BUTTON_PIN;
int FORWARD_BUTTON_PIN;
int SELECT_BUTTON_PIN;
int backButton = 0;
int frontButton = 0;
int selectButton = 0;

Servo servo1;
Servo servo2;
int userNum;
bool known = false, unknown = false;
short int c = 0;

void setup(){
  servo1.attach(SERVO_1_PIN);
  servo2.attach(SERVO_2_PIN);
  pinMode(BACK_BUTTON_PIN, INPUT);
  pinMode(FRONT_BUTTON_PIN, INPUT);
  pinMode(SELECT_BUTTON_PIN, INPUT);
  lcd.init(); 
  lcd.backlight();
  Serial.begin(9600);   // Initialize serial communications with the PC
  SPI.begin();      // Init SPI bus
  reader.PCD_Init();   // Init Card Reader
  reader.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  lcd.print("Please Scan Card");
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
}

void displayMed(string medName){
  lcd.print(medName);
}

void greetUser(string userName){
  lcd.print("WELCOME:");
  lcd.print(userName);
  wait(2000); //delay for 2s so user can read
  lcd.clear();
}

void auth(MFRC522 reader) { //authenticate user
  byte master[4] = {0x29, 0xFB, 0x56, 0xD3};//The hexidecimal UID
  if (reader.uid.uidByte[0] == master[0] && reader.uid.uidByte[1] == master[1] && reader.uid.uidByte[2] == master[2] && reader.uid.uidByte[3] == master[3]) {
    userNum = 1;
  }
  userNum = 2;
}

bool canTake(int medNum){
  if(userNum == 1){
    if(medNum == 1){
      if(u1_canTakeMed1){
        return true;
      }
    }else{
      if(u1_canTakeMed2){
        return true;
      }
    }
  }else{
    if(medNum == 1){
      if(u2_canTakeMed1){
        return true;
      }
    }else{
      if(u2_canTakeMed2){
        return true;
      }
    }
  }
  return false;
}

void dispense(int medNum){
  if(medNum == 1){
    servo1.write(SERVO_ROTATE);
    wait(100); //wait .1 second
    servo1.write(0-SERVO_ROTATE);
  }else{
    servo2.write(SERVO_ROTATE);
    wait(100);
    servo2.write(0-SERVO_ROTATE);
  }
}

void dispenseMedicine(int medNum, int userNum){
  if(canTake(medNum, userNum){
    lcd.clear();
    lcd.print("Dispensing...");
    dispense(medNum);
    lcd.clear();
  }else{
    lcd.clear();
    lcd.print("You cannot take that now.");
    wait(2000); //pause for 2 seconds
    lcd.clear();
  }
}

bool pressed = true;

void loop() {
  if(userNum == 0){
    c++;
    if (c >= 500) { // a time out event
      c = 0;
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
    auth(reader) 
    if (userNum = 1) { //checks which user swiped
      Serial.println("TRUE");
      lcd.clear();
      greetUser(USER1_NAME);
      digitalWrite(7, HIGH);
      digitalWrite(6, LOW);
      c = 0;
    }else{
      Serial.println("FALSE");
      lcd.clear();
      greetUser(USER2_NAME);
      digitalWrite(6, HIGH);
      digitalWrite(7, LOW);
      c = 0;
     }
  }else{
    if(pressed){
      lcd.write("<- Select Med ->");
      if(medNum == 1){
        lcd.write(MEDICATION1);
      }else if(medNum == 2){
        lcd.write(MEDICATION2);
      }
    }
    backButton = digitalRead(BACK_BUTTON_PIN);
    frontButton = digitalRead(FRONT_BUTTON_PIN);
    selectButton = digitalRead(SELECT_BUTTON_PIN);
    if(selectButton == HIGH){
      dispenseMedication(medNum);
      userNum = 0;
      pressed = true;
    }else if(frontButton == HIGH){
      medNum = 2;
      pressed = true;
    }else if(backButton == HIGH){
      medNum = 1;
      pressed = true;
    }else{
      pressed = false;
    }
    if(pressed){
      lcd.clear();
    }
  }
}
