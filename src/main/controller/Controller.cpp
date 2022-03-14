#ifndef _CONTROLLER_CPP_
#define _CONTROLLER_CPP_

Controller::Controller(String controllerName): controllerName(controllerName) {
    this->httpCommand = "";
}

Controller::~Controller() {
}

String Controller::getControllerName() {
    return this->controllerName;
}

void Controller::printController(Stream& Stream) {
    Stream.println("Current server: [name] " + this->getControllerName());
}

void Controller::pushCommand(String command) {
    this->httpCommand += command;
}

#endif // End for _CONTROLLER_CPP_