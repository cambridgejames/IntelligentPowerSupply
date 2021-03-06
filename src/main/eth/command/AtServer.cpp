#ifndef _AT_SERVER_CPP_
#define _AT_SERVER_CPP_

namespace AtCommandSpace {
    // 机器识别码
    static const unsigned char IDENTIFICATION_CODE[] = {0xED, 0xF2, 0xA3, 0x56, 0xCA, 0xDB, 0x91, 0x84, 0xB0, 0xD7};

    // 读写标志位
    static const unsigned char READ_CODE = 0x00;
    static const unsigned char WRITE_CODE = 0x01;

    // 参数范围（[0]: 首地址, [1]: 长度）
    static const unsigned char CONFIGURE_ARGS_RANGE[][2] = {
        {0x00, 0x04}, // LOCAL_IP_ADDR_RANGE 本地IP地址
        {0x04, 0x04}, // NET_MASK_RANGE 子网掩码
        {0x08, 0x04}, // GATE_WAY_RANGE 网关
        {0x10, 0x02}  // LOCAL_IP_PORT_RANGE 本地端口
    };
}

#include "AtServer.h"
#include "../../util/TimeUtil.hpp"
#include "../../util/NumberUtil.hpp"

/**
 * @brief Construct a new At Command:: At Command object
 * 
 * @param timeoutMills 
 * @param retryTimes 
 * @param serial 
 */
AtServer::AtServer(unsigned int timeoutMills, unsigned short retryTimes, Stream& serial):
    timeoutMills(timeoutMills), retryTimes(retryTimes), serial(serial) {
}

/**
 * 向设备发送AT命令并获取返回信息
 * 
 * @param commandCode 命令编号
 * @param isRead 只读标志位（true:读, false:写）
 * @return unsigned char* 返回值，需要手动释放
 */
unsigned char* AtServer::sendMessage(AtCommandSpace::AtCommandCode commandCode, bool isRead) {
    unsigned char requestCommand[AtServer::AT_COMMAND_LENGTH];
    // 拷贝设备识别码
    memmove(requestCommand, AtCommandSpace::IDENTIFICATION_CODE, sizeof(AtCommandSpace::IDENTIFICATION_CODE));
    // 设置读写标志位
    requestCommand[AtServer::AT_COMMAND_LENGTH - 3] = isRead ? AtCommandSpace::READ_CODE : AtCommandSpace::WRITE_CODE;
    // 设置参数
    unsigned char commandCodeRange[2];
    memmove(commandCodeRange, AtCommandSpace::CONFIGURE_ARGS_RANGE[commandCode], sizeof(commandCodeRange));
    memmove(requestCommand + AtServer::AT_COMMAND_LENGTH - 2, commandCodeRange, sizeof(commandCodeRange));

    // 发送命令
    if (!this->sendMessage(requestCommand, AtServer::AT_COMMAND_LENGTH)) {
        return nullptr;
    }
    unsigned char responseLength = commandCodeRange[1];
    unsigned char* responseCommand = new unsigned char[responseLength];
    for (int i = 0; i < responseLength; i++) {
        if (serial.available() > 0) {
            responseCommand[i] = serial.read();
        }
        if (serial.available() <= 0 && i < responseLength - 1) {
            delay(BETWEEN_CHAR_TIMEOUT_MILLS);
        }
    }
    serial.flush();
    return responseCommand;
}

/**
 * 发送命令并等待设备发送返回值
 *
 * @param requestCommand AT命令
 * @param commandLength 命令长度
 * @return true 设备在规定的超时时间和重试次数内成功返回
 * @return false 设备返回超时
 */
bool AtServer::sendMessage(const unsigned char* requestCommand, unsigned short commandLength) {
    for (unsigned short retry = 0; retry < this->retryTimes; retry++) {
        serial.flush();
        this->serial.write(requestCommand, AtServer::AT_COMMAND_LENGTH);
        unsigned long startTime = TimeUtil::getTimeMills();
        while (TimeUtil::getTimeMills() - startTime <= timeoutMills) {
            if (serial.available() > 0) {
                return true;
            }
            delay(BETWEEN_CHAR_TIMEOUT_MILLS);
        }
    }
    return false;
}

/**
 * 从设备读取IP地址
 *
 * @return String 设备当前的IP地址
 */
String AtServer::getLocalIpAddr() {
    AtCommandSpace::AtCommandCode commandCode = AtCommandSpace::AtCommandCode::LOCAL_IP_ADDR_RANGE;
    unsigned char* response = this->sendMessage(commandCode, true);
    if (response == nullptr) {
        return "";
    }
    unsigned short responseLength = AtCommandSpace::CONFIGURE_ARGS_RANGE[commandCode][1];
    String ipAddr = "";
    for (int i = 0; i < responseLength; i++) {
        ipAddr += "." + String(response[i]);
    }
    delete response;
    return ipAddr.substring(1);
}

/**
 * 从设备读取子网掩码
 *
 * @return String 设备当前的子网掩码
 */
short AtServer::getNetMask() {
    AtCommandSpace::AtCommandCode commandCode = AtCommandSpace::AtCommandCode::NET_MASK_RANGE;
    unsigned char* response = this->sendMessage(commandCode, true);
    if (response == nullptr) {
        return -1;
    }
    unsigned short responseLength = AtCommandSpace::CONFIGURE_ARGS_RANGE[commandCode][1];
    short netMask = 0;
    for (int i = 0; i < responseLength; i++) {
        netMask += NumberUtil::bitCount(response[i]);
    }
    delete response;
    return netMask;
}

/**
 * 从设备读取网关地址
 *
 * @return String 设备当前的网关地址
 */
String AtServer::getGateWay() {
    AtCommandSpace::AtCommandCode commandCode = AtCommandSpace::AtCommandCode::GATE_WAY_RANGE;
    unsigned char* response = this->sendMessage(commandCode, true);
    if (response == nullptr) {
        return "";
    }
    unsigned short responseLength = AtCommandSpace::CONFIGURE_ARGS_RANGE[commandCode][1];
    String ipAddr = "";
    for (int i = 0; i < responseLength; i++) {
        ipAddr += "." + String(response[i]);
    }
    delete response;
    return ipAddr.substring(1);
}

/**
 * 从设备读取端口号
 *
 * @return String 设备当前监听的端口号
 */
int AtServer::getLocalIpPort() {
    AtCommandSpace::AtCommandCode commandCode = AtCommandSpace::AtCommandCode::LOCAL_IP_PORT_RANGE;
    unsigned char* response = sendMessage(commandCode, true);
    if (response == nullptr) {
        return -1;
    }
    unsigned short responseLength = AtCommandSpace::CONFIGURE_ARGS_RANGE[commandCode][1];
    int port = 0;
    for (int i = 0; i < responseLength; i++) {
        port = port << sizeof(response[i]);
        port += response[i];
    }
    delete response;
    return port;
}

#endif // End for _AT_SERVER_CPP_
