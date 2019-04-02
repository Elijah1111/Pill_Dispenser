/*  ___   ___  ___  _   _  ___   ___   ____ ___  ____  
 * / _ \ /___)/ _ \| | | |/ _ \ / _ \ / ___) _ \|    \ 
 *| |_| |___ | |_| | |_| | |_| | |_| ( (__| |_| | | | |
 * \___/(___/ \___/ \__  |\___/ \___(_)____)___/|_|_|_|
 *                  (____/ 
 *In this sketch, we will show how to use your I2C LCD1602 display the 
 *static characters: “Hello, World!”
 * Tutorial URL http://osoyoo.com/2017/07/09/arduino-lesson-i2c-lcd1602-display/
 * CopyRight www.osoyoo.com
 */
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
void setup()
{
 lcd.init();                      // initialize the lcd 
 // Print a message to the LCD.
 lcd.backlight();
 lcd.print("Hello, world!");
}
void loop()
{
}
