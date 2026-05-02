# RA4M2-frame

基于 **Renesas RA4M2** 的综合测评项目框架，包含按键、LED、ADC、串口、定时调度等常用模块，适合在 `renesas_prj` 模板上快速开展功能开发与验证。

## 项目简介

本仓库用于瑞萨 RA4M2 开发板应用开发，核心目标：

- 提供可直接编译运行的工程骨架；
- 将常见外设能力模块化（`src/*.c`）；
- 便于在测评/课程/原型验证中快速扩展。

## 目录结构

```text
RA4M2-frame/
├── src/                # 用户应用层代码（按键、LED、串口、ADC、调度等）
├── ra_gen/             # FSP 生成代码（请尽量通过配置工具维护）
├── ra_cfg/             # FSP 配置头文件
├── ra/fsp/             # FSP 库源码
├── renesas_prj.uvprojx # Keil MDK 工程文件
└── README.md
```

## 开发环境建议

- MCU: Renesas RA4M2
- IDE: Keil MDK (ARMClang)
- 配置工具: Renesas FSP Configurator
- 下载调试: J-Link / 板载调试器

> 若首次接触项目，建议先阅读仓库中的中文说明文档与原理图资料（如 `RA4M2_Sensor-V1.0.pdf`、`相关链接.md`）。

## 当前功能模块

- `scheduler.c`：简易任务调度
- `key_app.c`：按键扫描与按下/抬起边沿事件
- `led_app.c`：LED 控制
- `adc_app.c`：ADC 采样
- `uart_app.c`：串口通信
- `tim_app.c`：定时器能力

## 按键事件说明（已修复）

按键模块使用**状态位图 + 边沿检测**：

- `key_down`：仅在按下瞬间置位
- `key_up`：仅在抬起瞬间置位

按键与位定义：

- K2 → `KEY2_MASK` (`1 << 0`)
- K3 → `KEY3_MASK` (`1 << 1`)
- K4 → `KEY4_MASK` (`1 << 2`)

这样可以避免“按下与抬起触发标志一致”的问题，也支持多个按键同时检测。

## 使用方式

1. 用 Keil 打开 `renesas_prj.uvprojx`；
2. 检查下载器/时钟/串口等硬件配置；
3. 编译并下载到开发板；
4. 在 `src/` 中按模块扩展业务逻辑。

## 注意事项

- `ra_gen/` 下代码由工具生成，建议通过 FSP 配置维护，避免手改后被覆盖；
- 按键为低电平按下逻辑，如硬件电路不同请同步调整；
- 若涉及中断与主循环共享变量，请按需增加 `volatile` 与临界区保护。

## 参考资料

- `相关链接.md`
- `RA4M2_Sensor-V1.0.pdf`
- `RA4M2-SENSOR.pdf`

---
如需我继续补充：
- 中英文双语 README；
- 模块时序图（按键/调度）；
- 快速移植指南（迁移到其他 RA 系列）。
