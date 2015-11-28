
#include <IRremoteESP8266.h>
#include "LightController.h"
#include "RemoteCodes.h"

#define RED_PIN 4
#define GREEN_PIN 5
#define BLUE_PIN 12

LightController light_controller(RED_PIN, GREEN_PIN, BLUE_PIN);


int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
    Serial.begin(115200);
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
String readStringUntil(Stream* stream, const char terminators[]) {
    int len_terminators = 0;
    while (terminators[len_terminators] != '\0') {
        len_terminators++;
    }

    String return_string = "";
    int next_byte = Serial.read();
    while ((char)next_byte != ' ' && (char)next_byte != '\n') {
        if (next_byte != -1) {
            return_string = return_string + (char)next_byte;
        }
        next_byte = Serial.read();
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
            Serial.println("error - invalid command: \"" + command + "\"");
        }
        
        while(Serial.available() && !isAlpha(Serial.peek())) {
            Serial.read();
        }
    }
}

