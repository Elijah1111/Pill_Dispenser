/*
 * Write to memory test
 * This code stores in EEPROM (we have 4Kb of ROM to write to)
 * Byte 0-31: User 1 Data
 * Byte 32-63: User 2 Data
 * Byte 32+: Medication Data
 * 
 * User Data Needed:
 * 
 * RFID chip (4 bytes) 
 * Is Child (1 byte)
 * Last Taken (24 bytes) 
 * 
 * Medication Data (88 bytes/med)
 * 
 * Name: 64 bytes
 * Dose (Child): 4 bytes (mg)
 * Dose (Adult): 4 bytes (mg)
 * Time Between Doses: 4 bytes (hours)
 * Size of Pill: 4 bytes (mg)
 * Pills Left: 4 bytes
 * 
 * 
 * Test Value (RFID 1): 0000 0000 0000 0000 (0)
 * Test Value (RFID 2): 1111 1111 1111 1111 (2^16)
 */

#include <EEPROM.h>


/*
 * C-struct to hold med data in an easily-writeable package
 * Size: 88
 */
struct med{
  char medName[16];
  int childDose;
  int adultDose;
  int timeBtwn;
  int pillsLeft;
}

/*
 * C-struct to hold user data in an easily-writeable package
 * Size: 29 bytes
 */
struct user{
  int rfid;
  bool isChild;
  int lastTaken[6];
}

void setup() {
  /*
   * save u1 data
   * save u2 data
   * 
   * save med data for all 6 meds
   */
}

void loop() {
  /* 
   *  read u1 data and output over serial
   */
}
