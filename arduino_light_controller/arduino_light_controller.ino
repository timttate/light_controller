
#include <IRremote.h>

const int RED_PIN = 9;
const int GREEN_PIN = 3;
const int BLUE_PIN = 10;

int red_brightness = 0;
int green_brightness = 0;
int blue_brightness = 0;

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
  
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  rgb_write(0, 0, 0);
  
  irrecv.enableIRIn(); // Start the receiver
}

void rgb_write(int red, int green, int blue) {
  red_brightness = red;
  green_brightness = green;
  blue_brightness = blue;
  
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}

void loop() {
  if (irrecv.decode(&results)) {
    if (results.bits != 0) {
      switch (results.value) {
        case IR_CODE_BRIGHTNESS_UP:
          break;
        case IR_CODE_BRIGHTNESS_DOWN:
          break;
        case IR_CODE_OFF:
          rgb_write(0, 0, 0);
          break;
        case IR_CODE_ON:
          rgb_write(16, 16, 16);
          break;
      }
    }
    irrecv.resume(); // Receive the next value
  }
}
