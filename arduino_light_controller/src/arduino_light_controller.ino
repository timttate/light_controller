
#include <IRremote.h>
#include "LightController.h"

#define RED_PIN 9
#define GREEN_PIN 5
#define BLUE_PIN 10

LightController light_controller(RED_PIN, GREEN_PIN, BLUE_PIN);

#define IR_CODE_BRIGHTNESS_UP 0xE5CFBD7F
#define IR_CODE_BRIGHTNESS_DOWN 0xA23C94BF
#define IR_CODE_OFF 0xE721C0DB
#define IR_CODE_ON 0xF0C41643

#define IR_CODE_RED 0x97483BFB
#define IR_CODE_GREEN 0x86B0E697
#define IR_CODE_BLUE 0x9EF4941F
#define IR_CODE_WHITE 0xA3C8EDDB

#define IR_CODE_RED_ORANGE 0x5BE75E7F
#define IR_CODE_BLUISH_GREEN 0xF377C5B7
#define IR_CODE_ULTRAMARINE 0xC101E57B
#define IR_CODE_FLASH 0x7EC31EF7

#define IR_CODE_ORANGE 0xD7E84B1B
#define IR_CODE_SPRING_GREEN 0xEE4ECCFB
#define IR_CODE_VIOLET 0x51E43D1B
#define IR_CODE_STROBE 0xFA3F159F

#define IR_CODE_AMBER 0x2A89195F
#define IR_CODE_DEEP_SKY_BLUE 0xF63C8657
#define IR_CODE_VIOLET_MAGENTA 0x44C407DB
#define IR_CODE_FADE 0xDC0197DB

#define IR_CODE_YELLOW 0x488F3CBB
#define IR_CODE_CYAN 0x13549BDF
#define IR_CODE_MAGENTA 0x35A9425F
#define IR_CODE_SMOOTH 0x9716BE3F

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
    // set timer1 to fast mode, to sync with timer0
    bitSet(TCCR1B, WGM12);

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

    process_serial_commands();
    delay(1);
}

// Similar to readStringUntil, but support multiple possible terminators
String readStringUntil(Stream* stream, char terminators[]) {
    int len_terminators = 0;
    while (terminators[len_terminators] != '\0') {
        len_terminators++;
    }

    String return_string = "";
    char next_char = Serial.read();
    while (next_char != ' ' && next_char != '\n') {
        if (next_char != -1) {
            return_string = return_string + next_char;
        }
        next_char = Serial.read();
    }

    return return_string;
}

void process_serial_commands () {
    if (Serial.available()) {
        String command = readStringUntil(&Serial, " \n");

        if (command == "set_state") {
            String param = Serial.readStringUntil('\n');
            if (param == "on") {
                Serial.println("Turning On!");
                light_controller.turn_on();
            } else if (param == "off") {
                Serial.println("Turning Off!");
                light_controller.turn_off();
            }
            else {
                Serial.println("bad param");
            }
        }
        else if (command == "set_bright") {
            int brightness = Serial.parseInt();
            Serial.print("Brightness: ");
            Serial.println(brightness);

            light_controller.set_brightness(brightness / 100.0);
        }
        else if (command == "set_rgb") {
            int red, green, blue;
            red = Serial.parseInt();
            Serial.print("Red: ");
            Serial.println(red);

            green = Serial.parseInt();
            Serial.print("Green: ");
            Serial.println(green);

            blue = Serial.parseInt();
            Serial.print("Blue: ");
            Serial.println(blue);

            light_controller.set_color_rgb(red, green, blue);
        }
        else if (command == "help") {
            Serial.println("Commands:");
            Serial.println("set_state [on|off]");
            Serial.println("set_bright [0-100]");
            Serial.println("set_rgb [r 0-255] [g 0-255] [b 0-255]");
        }
        else {
            Serial.println("error - invalid command");
        }
    }
}
