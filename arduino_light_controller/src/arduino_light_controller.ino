
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

#define IR_CODE_RED 0xFF9867
#define IR_CODE_GREEN 0xFFD827
#define IR_CODE_BLUE 0xFF8877
#define IR_CODE_WHITE 0xFFA857

#define IR_CODE_RED_ORANGE 0xFFE817
#define IR_CODE_BLUISH_GREEN 0xFF48B7
#define IR_CODE_ULTRAMARINE 0xFF6897
#define IR_CODE_FLASH 0xFFB24D

#define IR_CODE_ORANGE 0xFF02FD
#define IR_CODE_SPRING_GREEN 0xFF32CD
#define IR_CODE_VIOLET 0xFF20DF
#define IR_CODE_STROBE 0xFF00FF

#define IR_CODE_AMBER 0xFF50AF
#define IR_CODE_DEEP_SKY_BLUE 0xFF7887
#define IR_CODE_VIOLET_MAGENTA 0xFF708F
#define IR_CODE_FADE 0xFF58A7

#define IR_CODE_YELLOW 0xFF38C7
#define IR_CODE_CYAN 0xFF28D7
#define IR_CODE_MAGENTA 0xFFF00F
#define IR_CODE_SMOOTH 0xFF30CF

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

        case IR_CODE_RED:
          light_controller.set_color(1.0, 0.0, 0.0);
          break;
        case IR_CODE_GREEN:
          light_controller.set_color(0.0, 1.0, 0.0);
          break;
        case IR_CODE_BLUE:
          light_controller.set_color(0.0, 0.0, 1.0);
          break;
        case IR_CODE_WHITE:
          light_controller.set_color(1.0, 1.0, 1.0);
          break;

        case IR_CODE_RED_ORANGE:
          light_controller.set_color(1.0, 0.4, 0.0);
          break;
        case IR_CODE_BLUISH_GREEN:
          light_controller.set_color(0.0, 1.0, 0.4);
          break;
        case IR_CODE_ULTRAMARINE:
          light_controller.set_color(0.4, 0.0, 1.0);
          break;

        case IR_CODE_ORANGE:
          light_controller.set_color(1.0, 0.5, 0.0);
          break;
        case IR_CODE_SPRING_GREEN:
          light_controller.set_color(0.0, 1.0, 0.5);
          break;
        case IR_CODE_VIOLET:
          light_controller.set_color(0.5, 0.0, 1.0);
          break;

        case IR_CODE_AMBER:
          light_controller.set_color(1.0, 0.75, 0.0);
          break;
        case IR_CODE_DEEP_SKY_BLUE:
          light_controller.set_color(0.0, 1.0, 0.75);
          break;
        case IR_CODE_VIOLET_MAGENTA:
          light_controller.set_color(0.75, 0.0, 1.0);
          break;

        case IR_CODE_YELLOW:
          light_controller.set_color(1.0, 1.0, 0.0);
          break;
        case IR_CODE_CYAN:
          light_controller.set_color(0.0, 1.0, 1.0);
          break;
        case IR_CODE_MAGENTA:
          light_controller.set_color(1.0, 0.0, 1.0);
          break;

        case IR_CODE_FLASH:
          light_controller.set_color_rgb(255, 177, 110);
          break;
        case IR_CODE_STROBE:
          light_controller.set_color_rgb(255, 228, 206);
          break;
        case IR_CODE_FADE:
          light_controller.set_color_rgb(255, 254, 250);
          break;
        case IR_CODE_SMOOTH:
          light_controller.set_color_rgb(181, 205, 255);
          break;
      }
    }
    irrecv.resume(); // Receive the next value
  }
}
