#ifndef _HTTP_CONTROLLER_CPP_
#define _HTTP_CONTROLLER_CPP_

#include "HttpController.h"

HttpController::HttpController(String controllerName): controllerName(controllerName) {
    this->httpCommand = "";
}

HttpController::~HttpController() {
}

String HttpController::getControllerName() {
    return this->controllerName;
}

void HttpController::printController(Stream& Stream) {
    Stream.println("Current server: [name] " + this->getControllerName());
}

void HttpController::pushCommand(String command) {
    this->httpCommand += command;
}

#endif // End for _HTTP_CONTROLLER_CPP_