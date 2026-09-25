// main code for this screen test


#include <U8g2lib.h>                    // gives us a library that handles basic comms with the display

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, 22, 21);
// Breakdown of the above line
// controller: SH1106
// panel geometry: 128x64_NONAME
// buffer mode: F = full frame buffer - whole screen held in RAM and sent in one message
// interface: HW_I2C: esp32 hardware I2C peripheral

// args
// U8G2_R0: display rotation = none
// U8x8_PIN_NONE: sets no reset wire/no reset wire connected
// 22: clock pin
// 21: data pin


void setup() {
  u8g2.begin();                         // Initializes the screen
  u8g2.clearBuffer();                   // Clear the frame buffer
  u8g2.setFont(u8g2_font_ncenB14_tr);   // font select, full list here --> https://github.com/olikraus/u8g2/wiki/fntlist16#14-pixel-height
  u8g2.drawStr(14, 38, "It works!");    // coordinates (bottom left corner of text) and message (write to memory)
  u8g2.sendBuffer();                    // write to the screen
}

void run() {
  delay(2000);                          // 2 second delay
  u8g2.clearBuffer();                   // clear the frame buffer
  u8g2.drawStr(45, 15, "Top");          // x, y, message (write buffer)
  u8g2.sendBuffer();                    // send to screen

  delay(2000);                          // 2 second delay
  u8g2.clearBuffer();                   
  u8g2.drawStr(30, 64, "Bottom");       // x, y, message (write buffer)
  u8g2.sendBuffer();


  delay(2000);                          // 2 second delay
  u8g2.clearBuffer();                   
  u8g2.drawStr(1, 38, "Left");          // x, y, message (write buffer)
  u8g2.sendBuffer();


  delay(2000);                          // 2 second delay
  u8g2.clearBuffer();                   
  u8g2.drawStr(72, 38, "Right");        // x, y, message (write buffer)
  u8g2.sendBuffer();


  delay(2000);                          // 2 second delay
  u8g2.clearBuffer();                   
  u8g2.drawStr(30, 38, "Center");       // x, y, message (write buffer)
  u8g2.sendBuffer();

}