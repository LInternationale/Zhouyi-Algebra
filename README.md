# ☯️ Zhouyi-Algebra 周易代数 / JiajingOS 嘉靖OS

> 练得身形似鹤形，千株松下两函经；我来问道无余说，云在青天水在瓶。

**Zhouyi-Algebra** 是一个基于《周易》六十四卦体系构建的 C11 大数代数运算库与梅森素数推演系统。本项目摒弃了传统的二进制/十进制大数底层，转而采用“卦（gua）”作为基本数据单元。在这里，每一次进位都是阴阳的交替，每一次取模都是天机的流转。

---

## 核心特性 Features

本项目不仅是一个严肃的数学库，更是一个沉浸式的修仙模拟器：

- **卦象大数运算**：底层采用 6-bit 的 `gua` 结构体，完美契合六十四卦。支持大数加、减、乘、除、取模，以及左移等操作。
- **易理位运算**：实现了错卦（按位取反）、综卦（倒序）、互卦、交卦、变卦等符合《易经》规则的位操作。
- **沉浸式算卦**：内置 `suangua.c`，调用 SDL2 播放玉磬清音（如果玉磬没被严嵩贪没的话），通过步罡踏斗之法随机生成卦象。
- **梅森素数推演**：主程序使用卢卡斯-莱默检验法，以卦象大数推演并验证梅森素数，寻找天地间的绝对真理。

---

## 编译与运行 Build & Run

本项目使用 CMake 构建，依赖 SDL2 库以提供修仙所需的音效支持。

### 1. 环境依赖
你需要安装 CMake 以及 SDL2 和 SDL2_mixer：
- **macOS (Homebrew)**: `brew install cmake sdl2 sdl2_mixer`
- **Ubuntu/Debian**: `sudo apt install cmake libsdl2-dev libsdl2-mixer-dev`
- **Windows**: 建议使用 MSYS2 (MinGW-w64) 或 vcpkg 安装相关依赖。

### 2. 编译步骤
```bash
git clone https://github.com/yourusername/Zhouyi-Algebra.git
cd Zhouyi-Algebra
mkdir build && cd build
cmake ..
make
```

---

## 两函经 API

### 1. 易理代数核心 (`zhouyi_algebra.h`)

定义了基础的 6-bit 卦象结构（`gua`）以及基于卦象拼接的大数结构（`big_gua`）。它是一套易经推演引擎，顺便是一套大数运算系统。

#### 基础卦象与易理变换
| 方法 | 易理概念 | 释义 |
| :--- | :--- | :--- |
| `gua make_gua(unsigned char val)` | 起卦 | 从 `unsigned char` 构造一个 6-bit 的单卦结构体。 |
| `gua cuo(gua a)` | 错卦 | 阴阳爻互变（按位取反）。 |
| `gua zong(gua a)` | 综卦 | 卦象上下颠倒（位逆序）。 |
| `gua hu(gua a)` | 互卦 | 取原卦二三四爻为下卦，三四五爻为上卦重组。 |
| `gua jiao(gua a)` | 交卦 | 上下两卦位置互换。 |
| `gua bian(gua a, yao)` | 变卦 | 动爻生变（指定特定爻位进行翻转）。 |
| `const char* get_xiang_zhuan(unsigned char val)` | 观象玩辞 | 传入卦值，返回对应的《易经·象传》原文（如“天行健…”）。 |

#### 大衍之数运算
| 方法 | 功能描述 | 说明 |
| :--- | :--- | :--- |
| `big_gua big_gua_from_string(const char* str)` | 字符化数 | 将十进制字符串解析并转换为 Base-64 的卦象大数。 |
| `char* big_gua_to_string(big_gua bg)` | 数化字符 | 将卦象大数格式化回十进制字符串输出。需要手动释放内存。 |
| `big_gua big_gua_add(big_gua a, big_gua b)` | 大衍相加 | 大数加法，处理 64 进制的阴阳进位。 |
| `big_gua big_gua_mul(big_gua a, big_gua b)` | 大衍相乘 | 大数乘法，支持正负号（阴阳）的自动推导与位数动态扩展。 |
| `big_gua big_gua_div(big_gua a, big_gua b)` | 大衍整除 | 大数除法，支持正负号（阴阳）的自动推导。 |
| `big_gua big_gua_mod(big_gua a, big_gua b)` | 大衍取模 | 大数取模，由被除数决定正负号。 |
| `void print_big_gua_tight(big_gua bg)` | 展现卦象 | 使用Unicode进行八进制输出。 |
| `int big_gua_unsigned_cmp(big_gua a, big_gua b)` | 大数比对 | 比较两个卦象大数的绝对值大小。 |

### 2. 沉浸式起卦系统 (`suangua.h`)

为了让代数运算不那么枯燥，本模块引入了环境音效与随机数生成，模拟真实的道家推演仪式。需要玉熙宫（SDL2 & SDL2_mixer）环境支持。

| 方法 | 功能描述 | 说明 |
| :--- | :--- | :--- |
| `gua suan_gua()` | 步罡踏斗演卦 | 很有仪式感的返回一个随机的卦象。 |

---

## 参与贡献 Contributing

欢迎各位道友提交 PR 或 Issue，玉熙宫的大门永远为你敞开。

**License:** MIT License
