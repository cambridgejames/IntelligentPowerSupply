#ifndef _NUMBER_UTIL_HPP_
#define _NUMBER_UTIL_HPP_

class NumberUtil {

private:
    NumberUtil() {};
    ~NumberUtil() {};

public:
    static unsigned int bitCount(int num);
};

// Implementation of methods

/**
 * 计算数值的二进制中1的个数
 * 
 * @param num 数字
 * @return unsigned int 二进制中1的个数
 */
unsigned int NumberUtil::bitCount(int num) {
    return num == 0 ? 0 : bitCount(num >> 1) + (num & 1);
}

#endif // End for _NUMBER_UTIL_HPP_
