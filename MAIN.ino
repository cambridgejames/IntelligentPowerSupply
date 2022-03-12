void setup() {
    Serial.begin(115200, SERIAL_8N1);
    Serial.println("Hello World!");
}

void loop() {
    if (Serial.available() <= 0) {
        // Serial.println("None to read.");
        // delay(1000);
        return;
    }

    while (Serial.available() > 0) {
        int currentChar = Serial.read();
        Serial.print((char) currentChar);
        // Serial.print(" ");
    }
    Serial.println("Done.");
}
