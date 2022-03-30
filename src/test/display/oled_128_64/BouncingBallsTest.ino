#ifndef _BOUNCING_BALLS_TEST_INO_
#define _BOUNCING_BALLS_TEST_INO_

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// 屏幕参数
#define SCREEN_WIDTH   128
#define SCREEN_HEIGHT  64
#define OLED_RESET     4
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// 显示参数
#define CIRCLE_RADIO   2   // 小球的半径（像素）
#define NUMBER_OF_BALL 10  // 小球的数量

int OMEGA[] = {1400,1300,1200,1100,1000,900,800,700,600,500}; // 小球的跳动周期（毫秒）

// 函数声明
int getX(int index, int number, int width);
int getY(unsigned long time, int omega, int height, int radio);

/**
 * @brief 初始化屏幕参数
 */
void setup(void) {
    display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    display.setTextSize(1);
    display.display();
}

unsigned long timeLastFrame = 0;

/**
 * @brief 循环显示动画帧
 */
void loop(void) {
    display.clearDisplay();
    unsigned long time = millis();
    for (int i = 0; i < NUMBER_OF_BALL; i++) {
        display.fillCircle(getX(i + 1, NUMBER_OF_BALL, SCREEN_WIDTH),
            SCREEN_HEIGHT - getY(time, OMEGA[i], SCREEN_HEIGHT - 2, CIRCLE_RADIO) - 2,
            CIRCLE_RADIO, SSD1306_WHITE);
    }
    display.drawLine(0, SCREEN_HEIGHT - 1, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, SSD1306_WHITE);

    // 计算并显示FPS
    unsigned long timeAfterFrame = millis();
    float fps = 1000. / (timeAfterFrame - timeLastFrame);
    display.setCursor(0,0);
    display.println("FPS:" + String(fps, 1));
    timeLastFrame = timeAfterFrame;
    display.display();
}

/**
 * @brief 计算小球的横坐标
 * 
 * @param index 小球的编号（从1开始）
 * @param number 小球的总数
 * @param width 屏幕的宽度（像素）
 * @return int 小球的横坐标
 */
int getX(int index, int number, int width) {
    return (int) (((float) (width * index)) / (number + 1));
}

/**
 * @brief 计算小球的纵坐标
 * 
 * @param time 当前时间戳
 * @param omega 小球的运动周期（毫秒）
 * @param height 屏幕的高度（像素）
 * @param radio 小球的半径（像素）
 * @return int 小球的纵坐标
 */
int getY(unsigned long time, int omega, int height, int radio) {
    unsigned long x = time % omega;
    if (x > omega / 2) {
        x = omega - x;
    }
    float h = height - 2 * radio;
    float a = 4 * h / omega / omega;
    return (int) (-a * x * x + h + radio);
}

#endif // End for _BOUNCING_BALLS_TEST_INO_
