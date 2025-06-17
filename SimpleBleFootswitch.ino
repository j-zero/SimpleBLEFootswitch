#include <Arduino.h>
#include "Button.h"       // https://github.com/esp-arduino-libs/ESP32_Button
#include "src/ESP32_BLE_Keyboard/BleKeyboard.h"  // https://github.com/T-vK/ESP32-BLE-Keyboard (with NimBLE: https://github.com/h2zero/NimBLE-Arduino, v2.3.1)

BleKeyboard bleKeyboard;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE...");
  bleKeyboard.begin();


  // initializing a button
  Button *btn = new Button(GPIO_NUM_9, false);

  btn->attachPressDownEventCb(&onButtonPressDownCb, NULL);
  btn->attachPressUpEventCb(&onButtonPressUpCb, NULL);
  btn->attachPressDownEventCb(&onButtonPressDownRepeatCb, NULL);
  btn->attachSingleClickEventCb(&onButtonSingleClickCb,NULL);
  btn->attachSingleClickEventCb(&onButtonSingleClickRepeatCb,NULL);
  btn->unregisterPressDownEventCb(&onButtonPressDownCb);
  btn->detachSingleClickEvent();


}


static void onButtonPressDownCb(void *button_handle, void *usr_data) {
    Serial.println("Button pressed down");
}
static void onButtonPressDownRepeatCb(void *button_handle, void *usr_data)
{
    Serial.println("Button press down repeat");
    if(bleKeyboard.isConnected())
      bleKeyboard.write(KEY_RETURN);
}
static void onButtonPressUpCb(void *button_handle, void *usr_data) {
    Serial.println("Button press Up");
}
static void onButtonSingleClickCb(void *button_handle, void *usr_data) {
    Serial.println("Button single click");
}
static void onButtonSingleClickRepeatCb(void *button_handle, void *usr_data)
{
    Serial.println("Button single click repeat");
}


void loop() {
  Serial.println("Heartbeet");
  delay(5000);
}
