#define BAT_ADC       2
#define BUTTON_PIN_1  GPIO_NUM_8
#define BUTTON_PIN_2  GPIO_NUM_9


#include <Arduino.h>

#include "src/ESP32-BLE-Keyboard-master/BleKeyboard.h"
#include "src/Button2-master/src/Button2.h"
#include "esp_adc_cal.h"




BleKeyboard bleKeyboard("BLE Footswitch","datanpir.at");
Button2 button_1, button_2;
uint32_t battery_level = 0;


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

  battery_level = getBatteryPercentage();
  bleKeyboard.setBatteryLevel(battery_level);

}

void loop() {

  button_1.loop();
  button_2.loop();

  uint32_t new_battery_level =  getBatteryPercentage();
  if(new_battery_level != battery_level){
    battery_level = new_battery_level;
    bleKeyboard.setBatteryLevel(battery_level);
  }

  //if(bleKeyboard.isConnected()) {
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
  //}


}

uint32_t readADC_Cal(int ADC_Raw)
{
    esp_adc_cal_characteristics_t adc_chars;
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc_chars);
    return (esp_adc_cal_raw_to_voltage(ADC_Raw, &adc_chars));
}

double getBatteryVoltage(void)
{
    return ((readADC_Cal(analogRead(BAT_ADC))) * 2) / 1000.0;
}

uint32_t getBatteryPercentage(void)
{
    double v = getBatteryVoltage();
    return static_cast<int>(round(min(max(((v - 3.3) / (4.2 - 3.3)) * 100, 0.0), 100.0)));
}