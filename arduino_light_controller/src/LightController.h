
#ifndef LightState_h
#define LightState_h

#include "Arduino.h"
#include "math.h"

const int GAMMA = 2;

class LightController {
public:
    LightController(int red_pin, int green_pin, int blue_pin) : 
        RED_PIN(red_pin), GREEN_PIN(green_pin), BLUE_PIN(blue_pin) {
            red = 1.0;
            green = 1.0;
            blue = 1.0;
            brightness = 1.0;
            is_on = true;
        };

    void setup() {
        pinMode(RED_PIN, OUTPUT);
        pinMode(GREEN_PIN, OUTPUT);
        pinMode(BLUE_PIN, OUTPUT);
        update_output();
    }

    void set_color(float red, float green, float blue) {
        this->red = red;
        this->green = green;
        this->blue = blue;
        update_output();
    }

    void set_brightness(float brightness) {
        this->brightness = brightness;
        update_output();
    }

    void turn_on() {
        is_on = true;
        update_output();
    }

    void turn_off() {
        is_on = false;
        update_output();
    }

    void bright_up() {
        brightness = min(1.0, brightness + 0.07);
        update_output();
    }

    void bright_down() {
        brightness = max(0.16, brightness - 0.07);
        update_output();
    }

private:
    void update_output() {
        float bright_out = is_on ? brightness : 0.0;
        int red_out = min(255, 255 * pow(red * bright_out, GAMMA));
        int green_out = min(255, 255 * pow(green * bright_out, GAMMA));
        int blue_out = min(255, 255 * pow(blue * bright_out, GAMMA));

        analogWrite(RED_PIN, red_out);
        analogWrite(GREEN_PIN, green_out);
        analogWrite(BLUE_PIN, blue_out);
        Serial.print(red_out);
        Serial.print('\t');
        Serial.print(green_out);
        Serial.print('\t');
        Serial.print(blue_out);
        Serial.println('\t');
    }

    const int RED_PIN;
    const int GREEN_PIN;
    const int BLUE_PIN;

    float red;
    float green;
    float blue;
    float brightness;

    bool is_on;
};

#endif
