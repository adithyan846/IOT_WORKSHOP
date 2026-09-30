#define LED_PIN LED_BUILTIN

void setup() {
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    digitalWrite(LED_PIN, LOW);   // ON
    delay(1000);

    digitalWrite(LED_PIN, HIGH);  // OFF
    delay(1000);
}