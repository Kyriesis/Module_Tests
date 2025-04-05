# 🧪 Module_Tests

本项目基于 [PlatformIO](https://platformio.org/) 开发，使用 **ESP32-S3 DevKit** 控制 **PCF8575 I2C IO 扩展模块**，用于多路数字输入（按键）与输出（LED）测试，支持 FreeRTOS 多任务，适合嵌入式控制器模块化功能验证。

---

## 🔧 项目概览

- 💡 基于 ESP32-S3 开发板（PlatformIO 环境）
- 📦 使用 PCF8575 I2C IO 扩展模块（16位）
- 🔁 实现低频率、稳定的开关输入轮询
- 💡 LED 状态反馈
- ✅ 支持 FreeRTOS 多任务结构
- 📟 串口调试信息输出

---

## 📁 项目结构

Module_Tests/ ├── .vscode/ # VS Code 工作区配置（可选） ├── include/ # 公共头文件目录 ├── lib/ # 自定义库 ├── src/ # 主程序源码（main.cpp） ├── test/ # 单元测试（可选） ├── .gitignore # Git 忽略列表 └── platformio.ini # PlatformIO 配置文件



---

## 📚 依赖库

在 `platformio.ini` 中使用以下依赖项：

```ini
lib_deps =
  https://github.com/xreef/PCF8575_library.git

快速开始
1️⃣ 克隆项目
bash
复制
编辑
git clone https://github.com/Kyriesis/Module_Tests.git
cd Module_Tests
2️⃣ 打开 VS Code + PlatformIO 插件
或使用 CLI 编译：

bash
复制
编辑
pio run -t upload
pio device monitor


 默认硬件连接
组件	ESP32-S3 GPIO	说明
PCF8575 SDA	GPIO12	I2C 数据线
PCF8575 SCL	GPIO11	I2C 时钟线
LED	GPIO21	本地 LED 输出
MODE_SWITCH	PCF8575 P0	外部拨钮输入

例逻辑功能
PCF8575 的第0位（P0）作为开关输入

当拨钮按下（低电平）时，LED 熄灭；断开时 LED 亮起

支持通过串口查看输入状态变化

任务使用 xTaskCreatePinnedToCore 固定调度


后续建议功能扩展
OLED 状态显示

所有 16 路 IO 扩展应用测试

状态上传至 MQTT / Web UI

多路按键输入/组合控制


项目由 David Zhu / Kyriesis 发起，用于嵌入式 IO 控制方案验证
GitHub: github.com/Kyriesis

本项目采用 MIT 开源协议，欢迎 Fork、使用、修改、引用 🌱