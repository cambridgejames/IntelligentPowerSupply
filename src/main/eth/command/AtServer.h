#ifndef _AT_SERVER_H_
#define _AT_SERVER_H_

namespace AtCommandSpace {
    enum AtCommandCode {
        LOCAL_IP_ADDR_RANGE, // 本地IP地址
        NET_MASK_RANGE, // 子网掩码
        GATE_WAY_RANGE, // 网关
        LOCAL_IP_PORT_RANGE, // 本地端口
    };
}

class AtServer {

private:
    // 等待建立TCP连接的默认超时时间
    static const unsigned int TIMEOUT_MILLS_DEFAULT = 5000;
    // 超时后默认重试次数
    static const unsigned short TIMEOUT_RETRY_DEFAULT = 5;
    // 请求命令长度
    static const unsigned short AT_COMMAND_LENGTH = 13;
    // 返回命令字符间最大等待时间
    static const unsigned short BETWEEN_CHAR_TIMEOUT_MILLS = 10;

private:
    unsigned int timeoutMills;
    unsigned short retryTimes;
    Stream& serial;

public:
    AtServer(Stream& serial): AtServer(TIMEOUT_MILLS_DEFAULT, TIMEOUT_RETRY_DEFAULT, serial) {};
    AtServer(unsigned int timeoutMills, unsigned short retryTimes, Stream& serial);
    ~AtServer() {}

    String getLocalIpAddr(void);
    String getNetMask(void);
    String getGateWay(void);
    String getLocalIpPort(void);

public:
    // Getter and Setter
    unsigned int getTimeoutMills() const { return this->timeoutMills; };
    void setTimeoutMills(const unsigned int timeoutMills) { this->timeoutMills = timeoutMills; };
    unsigned short getRetryTimes() const { return this->retryTimes; };
    void setRetryTimes(const unsigned short retryTimes) { this->retryTimes = retryTimes; };

private:
    unsigned char* sendMessage(AtCommandSpace::AtCommandCode commandCode, bool isRead);
    bool sendMessage(const unsigned char* requestCommand, unsigned short commandLength);
};

#include "AtServer.cpp"

#endif // End for _AT_SERVER_H_
