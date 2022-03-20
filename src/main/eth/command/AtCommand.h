#ifndef _AT_COMMAND_H_
#define _AT_COMMAND_H_

namespace AtCommandSpace {
    enum AtCommandCode {
        LOCAL_IP_ADDR_RANGE, // 本地IP地址
        NET_MASK_RANGE, // 子网掩码
        GATE_WAY_RANGE, // 网关
        LOCAL_IP_PORT_RANGE, // 本地端口
    };
}

class AtCommand {

private:
    // 等待建立TCP连接的超时时间
    static const unsigned int TIMEOUT_MILLS_DEFAULT = 5000;
    // 请求命令长度
    static const unsigned short AT_COMMAND_LENGTH = 13;
    // 返回命令字符间最大等待时间
    static const unsigned short BETWEEN_CHAR_TIMEOUT_MILLS = 10;

private:
    Stream& serial;

public:
    AtCommand(Stream& serial);
    ~AtCommand() {}

    String getLocalIpAddr(unsigned int timeoutMills = AtCommand::TIMEOUT_MILLS_DEFAULT);
    String getNetMask(unsigned int timeoutMills = AtCommand::TIMEOUT_MILLS_DEFAULT);
    String getGateWay(unsigned int timeoutMills = AtCommand::TIMEOUT_MILLS_DEFAULT);
    String getLocalIpPort(unsigned int timeoutMills = AtCommand::TIMEOUT_MILLS_DEFAULT);

private:
    unsigned char* sendMessage(AtCommandSpace::AtCommandCode commandCode,
        bool isRead, unsigned int timeoutMills);
    bool waitForResponse(unsigned int timeoutMills);
};

#include "AtCommand.cpp"

#endif // End for _AT_COMMAND_H_
