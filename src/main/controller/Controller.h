#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

enum class HttpRequestMethod {
    GET, POST, PUT, DELET, PATCH
};

class Controller {
private:
    String controllerName;
    String httpCommand;

public:
    Controller(String controllerName);
    ~Controller();

    String getControllerName();
    void printController(Stream& stream);

    void pushCommand(String command);

private:

};

#include "Controller.cpp"

#endif // End for _CONTROLLER_H_