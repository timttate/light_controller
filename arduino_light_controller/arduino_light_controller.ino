
#include <IRremote.h>
#include "LightController.h"

#define RED_PIN 9
#define GREEN_PIN 3
#define BLUE_PIN 10

LightController light_controller(RED_PIN, GREEN_PIN, BLUE_PIN);

#define IR_CODE_BRIGHTNESS_UP 0xFF906F
#define IR_CODE_BRIGHTNESS_DOWN 0xFFB847
#define IR_CODE_OFF 0xFFF807
#define IR_CODE_ON 0xFFB04F

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  light_controller.setup();
  
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    if (results.bits != 0) {
      switch (results.value) {
        case IR_CODE_BRIGHTNESS_UP:
          light_controller.bright_up();
          Serial.println("up");
          break;
        case IR_CODE_BRIGHTNESS_DOWN:
          light_controller.bright_down();
          Serial.println("down");
          break;
        case IR_CODE_OFF:
          light_controller.turn_off();
          Serial.println("off");
          break;
        case IR_CODE_ON:
          light_controller.turn_on();
          Serial.println("on");
          break;
      }
    }
    irrecv.resume(); // Receive the next value
  }
}
