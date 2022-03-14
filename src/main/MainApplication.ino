#include <ArduinoHttpServer.h>
#include <LiquidCrystal.h>

#include <Arduino.h>

#include "controller/Controller.h"

// #define eunmToString(x) #x
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

template <size_t MAX_BODY_SIZE>
void solveErrorRequest(ArduinoHttpServer::StreamHttpRequest<MAX_BODY_SIZE>& httpRequest);

void setup() {
    Serial.begin(115200, SERIAL_8N1);
    // Serial.println("Http server started.");

    Controller *controller = new Controller("Test Controller");
    // controller->printController(Serial);

    initIfConfig(Serial);
    // lcd.begin(16, 2);
    // lcd.print("Http server started.");

    delete controller;
}

void initIfConfig(Stream& serial) {
    unsigned char ifConfig[] = {0xED, 0xF2, 0xA3, 0x56, 0xCA, 0xDB, 0x91, 0x84, 0xB0, 0xD7, 0x00, 0x00, 0x04};
    int ifConfigLength = sizeof(ifConfig) / sizeof(ifConfig[0]);
    serial.flush();
    serial.write(ifConfig, ifConfigLength);
    delay(500);

    serial.println();
    lcd.begin(16, 2);
    String ip = "";
    while(serial.available() > 0) {
        int current = serial.read();
        ip += String(current) + ".";
        delay(2);
    }
    lcd.print(ip);
    serial.println(ip);
}

void loop() {
    lcd.setCursor(0, 1);
    lcd.print(millis());

    // Serial.println("Http server loop.");
    // ArduinoHttpServer::StreamHttpRequest<1024> httpRequest(Serial);
    // if (!httpRequest.readRequest()) {
    //     // solveErrorRequest(httpRequest);
    //     return;
    // }
    // Serial.println(httpRequest.getResource().toString());
    // Serial.println(eunmToString(httpRequest.getMethod()));
    // Serial.println("HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: 46\r\n\r\n{\"username\":\"admin\",\"password\":\"Changeme_123\"}");
}

/**
 * Http错误处理方法
 * 
 * @tparam MAX_BODY_SIZE 最大Body尺寸
 * @param httpRequest HTTP请求
 */
template <size_t MAX_BODY_SIZE>
void solveErrorRequest(ArduinoHttpServer::StreamHttpRequest<MAX_BODY_SIZE>& httpRequest) {
    ArduinoHttpServer::StreamHttpErrorReply httpReply(Serial, httpRequest.getContentType());
    const char *pErrorStr(httpRequest.getError().cStr());
    String errorStr(pErrorStr);
    httpReply.send(errorStr);
    Serial.println("[ERROR] " + errorStr);
}
