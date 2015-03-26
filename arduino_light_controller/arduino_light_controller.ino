
#include <IRremote.h>

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    if (results.bits != 0) {
      Serial.println(results.value, HEX);
      //dump(&results);
    }
    irrecv.resume(); // Receive the next value
  }
}
