#include <Arduino.h>
#include <Wire.h>
#include "PCF8575.h"

// I2C 地址
#define PCF8575_ADDR 0x20
#define MODE_SWITCH_PIN 0     // PCF8575 第 0 位
#define LED_PIN 21            // 板载 LED 或自定义引脚

// 创建 PCF8575 实例
PCF8575 pcf8575(PCF8575_ADDR);

// 模式状态
bool modeState = false;

// 任务函数声明（必须写在前面）
void TaskInput(void *pvParameters);

void setup() {
  Serial.begin(115200);
  delay(500);

  // 初始化 I2C（S3 推荐手动指定 SDA/SCL）
  Wire.begin(11, 12);  // GPIO11 = SDA，GPIO12 = SCL，确保和你接线一致

  // 初始化 PCF8575 模块
  if (pcf8575.begin()) {
    Serial.println("✅ PCF8575 初始化成功");
  } else {
    Serial.println("❌ PCF8575 初始化失败");
  }

  pcf8575.pinMode(MODE_SWITCH_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  // 创建输入读取任务，运行在 Core 1
  xTaskCreatePinnedToCore(TaskInput, "TaskInput", 4096, NULL, 1, NULL, 1);
}

void loop() {
  // 主循环可以什么都不干，任务线程负责读取
  delay(1000);
}

// PCF8575 按键状态读取任务（IO稳定读取）
void TaskInput(void *pvParameters) {
  while (1) {
    modeState = (pcf8575.digitalRead(MODE_SWITCH_PIN) == LOW);  // 低电平为按下
    digitalWrite(LED_PIN, modeState ? LOW : HIGH);  // LED 控制

    Serial.print("MODE SWITCH: ");
    Serial.println(modeState ? "ON（按下）" : "OFF（断开）");

    // 稳定读取延时，推荐 20ms
    vTaskDelay(20 / portTICK_PERIOD_MS);
  }
}
