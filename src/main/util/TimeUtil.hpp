#ifndef _TIME_UTIL_HPP_
#define _TIME_UTIL_HPP_

class TimeUtil {

private:
    static const unsigned short NUM_MILLS_PER_SECOND = 1000;
    static const unsigned short NUM_SECONDS_PER_MINUTE = 60;
    static const unsigned short NUM_MINUTES_PER_HOUR = 60;

    static const unsigned int MINUTES = NUM_MILLS_PER_SECOND * NUM_SECONDS_PER_MINUTE;
    static const unsigned int HOURS = MINUTES * NUM_MINUTES_PER_HOUR;

private:
    TimeUtil() {};
    ~TimeUtil() {};

public:
    static unsigned long getTimeMills();
    static String getTime();
};

// Implementation of methods

/**
 * 获取系统从启动以来的运行时间（单位：毫秒）
 * 
 * @return unsigned long 运行总时间
 */
unsigned long TimeUtil::getTimeMills() {
    return millis();
}

/**
 * 获取系统从启动以来的运行时间（格式：时:分:秒）
 * 
 * @return String 运行总时间
 */
String TimeUtil::getTime() {
    unsigned long upSeconds = TimeUtil::getTimeMills() / TimeUtil::NUM_MILLS_PER_SECOND;
    unsigned short hours = (unsigned short) (upSeconds / TimeUtil::NUM_MINUTES_PER_HOUR / TimeUtil::NUM_SECONDS_PER_MINUTE);

    unsigned short minuts = (unsigned short) (upSeconds / TimeUtil::NUM_SECONDS_PER_MINUTE);
    unsigned short realMinuts = minuts >= 60 ? minuts - 60 * hours : minuts;

    unsigned long seconds = (hours * TimeUtil::NUM_MINUTES_PER_HOUR * TimeUtil::NUM_SECONDS_PER_MINUTE)
        + (realMinuts * TimeUtil::NUM_SECONDS_PER_MINUTE);
    unsigned short realSeconds = (unsigned short) (upSeconds - seconds);
    return String(hours)
        + (realMinuts >= 10 ? ":" : ":0") + String(realMinuts)
        + (realSeconds >= 10 ? ":" : ":0") + String(realSeconds);
}

#endif // End for _TIME_UTIL_HPP_