#ifndef _HTTP_CONTROLLER_H_
#define _HTTP_CONTROLLER_H_

enum class HttpRequestMethod {
    GET, POST, PUT, DELET, PATCH
};

class HttpController {
private:
    String controllerName;
    String httpCommand;

public:
    HttpController(String controllerName);
    ~HttpController();

    String getControllerName();
    void printController(Stream& stream);

    void pushCommand(String command);

private:

};

#include "HttpController.cpp"

#endif // End for _HTTP_CONTROLLER_H_