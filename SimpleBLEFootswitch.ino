#define BUTTON_PIN_1  GPIO_NUM_8
#define BUTTON_PIN_2  GPIO_NUM_9

#include <Arduino.h>

#include "src/ESP32-BLE-Keyboard-master/BleKeyboard.h"
#include "src/Button2-master/src/Button2.h"

BleKeyboard bleKeyboard("BLE HID Footswitch","datanpir.at");
Button2 button_1, button_2;

void handler(Button2& btn) {
  switch (btn.getType()) {
    case single_click:
    if(bleKeyboard.isConnected())
      if(btn == button_1 ){
        bleKeyboard.write(KEY_BACKSPACE);
      }
      else if(btn == button_2){
        bleKeyboard.write(KEY_SPACE);
      }


      break;
    case double_click:
      
      break;
    default:
      break;
  }
  Serial.print("click ");
  Serial.print("on button #");
  Serial.print((btn == button_1) ? "1" : "2");
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();

  button_1.begin(BUTTON_PIN_1);
  button_1.setClickHandler(handler);
  button_1.setDoubleClickHandler(handler);

  button_2.begin(BUTTON_PIN_2);
  button_2.setClickHandler(handler);
  button_2.setDoubleClickHandler(handler);
}

void loop() {

  button_1.loop();
  button_2.loop();

  if(bleKeyboard.isConnected()) {
    //Serial.println("Sending 'Hello world'...");
    //bleKeyboard.print("Hello world");

    

    
   // bleKeyboard.write(KEY_RETURN);

    //bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);


   //
   // Below is an example of pressing multiple keyboard modifiers 
   // which by default is commented out.
    /*
    Serial.println("Sending Ctrl+Alt+Delete...");
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.press(KEY_DELETE);
    delay(100);
    bleKeyboard.releaseAll();
    */
  }


}