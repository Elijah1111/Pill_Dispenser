

/*
 * Constants: Created because the actual permanent memory is small
 */

string MEDICATION1 = "Mini M&M";
string MEDICATION2 = "Robin's Egg";
int MEDICATION1_TO_DISPENSE = 1;
int MEDICATION2_TO_DISPENSE = 2;
string USER1_NAME = "The Grand Wizard, Tim";
string USER2_NAME = "SwagDaddi3000";
byte U1_RFID[4] = {0x29, 0xFB, 0x56, 0xD3};
bool u1_canTakeM1 = true;
bool u2_canTakeM1 = false;
bool u1_canTakeM2 = true;
bool u2_canTakeM2 = true;


int DISTANCE_TO_ROTATE_SERVO = 90;


void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
}

void dispenseMedicine(int medNum, int userNum){
  if(canTake(medNum, userNum){
    dispense(medNum);
  }else{
    displayOut("You cannot take that now.");
  }
}


/*
void dispense(int medNum){

}
*/
bool canTake(int medNum, int userNum){
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
