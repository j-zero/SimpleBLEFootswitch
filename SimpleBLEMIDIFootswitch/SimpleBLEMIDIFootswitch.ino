#include <Arduino.h>
#include "src/BLE-MIDI/src/BLEMidi.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing bluetooth");
  BLEMidiServer.begin("FooBLE");
  Serial.println("Waiting for connections...");
  BLEMidiServer.enableDebugging();  // Uncomment if you want to see some debugging output from the library (not much for the server class...)
}

void loop() {
  if(BLEMidiServer.isConnected()) {             // If we've got a connection, we send an A4 during one second, at full velocity (127)
      BLEMidiServer.noteOn(0, 69, 127);
      delay(1000);
      BLEMidiServer.noteOff(0, 69, 127);        // Then we make a delay of one second before returning to the beginning of the loop
      delay(1000);
  }
}