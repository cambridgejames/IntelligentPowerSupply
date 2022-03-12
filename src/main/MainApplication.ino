#include <ArduinoHttpServer.h>

#include <Arduino.h>

// #define eunmToString(x) #x

template <size_t MAX_BODY_SIZE>
void solveErrorRequest(ArduinoHttpServer::StreamHttpRequest<MAX_BODY_SIZE>& httpRequest);

void setup() {
    Serial.begin(115200, SERIAL_8N1);
    Serial.println("Http server started.");
}

void loop() {
    // Serial.println("Http server loop.");
    ArduinoHttpServer::StreamHttpRequest<1024> httpRequest(Serial);
    if (!httpRequest.readRequest()) {
        // solveErrorRequest(httpRequest);
        return;
    }
    // Serial.println(httpRequest.getResource().toString());
    // Serial.println(eunmToString(httpRequest.getMethod()));
    Serial.println("HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: 46\r\n\r\n{\"username\":\"admin\",\"password\":\"Changeme_123\"}");
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
