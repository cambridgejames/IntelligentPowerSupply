#include <LiquidCrystal.h>

#include <Arduino.h>

#include "eth/command/AtServer.h"
#include "controller/HttpController.h"
#include "util/TimeUtil.hpp"

// #define eunmToString(x) #x
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
AtServer atServer(Serial);

void setup() {
    Serial.begin(115200, SERIAL_8N1);
    lcd.begin(16, 2);
    lcd.print("Booting...");

    unsigned long startTime = TimeUtil::getTimeMills();
    String ipAddr = atServer.getLocalIpAddr();
    unsigned long timeCost = TimeUtil::getTimeMills() - startTime;
    lcd.setCursor(0, 0);
    lcd.print(ipAddr.length() == 0 ? "Timed out." : ipAddr);

    lcd.setCursor(0, 1);
    lcd.print(timeCost);

    HttpController *controller = new HttpController("Test Controller");
    delete controller;
}

void loop() {
    // lcd.setCursor(0, 1);
    // lcd.print("UpTime: " + TimeUtil::getTime());
}
