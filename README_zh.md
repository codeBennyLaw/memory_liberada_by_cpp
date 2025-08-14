# MemoryLiberada

[![Language](https://img.shields.io/badge/Language-English-blue.svg)](README.md) [![Language](https://img.shields.io/badge/语言-中文-red.svg)](README_zh.md)

一个通过调整运行中进程工作集来优化系统内存使用的Windows应用程序。

## 概述

MemoryLiberada是一个C++应用程序，通过调整运行中进程的工作集来帮助释放系统内存。它会显示优化前后的内存状态，展示释放的内存量。

该应用程序通过调用`SetProcessWorkingSetSize`并使用特殊参数，告诉Windows修剪每个进程的工作集，这有助于释放物理内存。

## 功能特点

- 显示总物理内存和可用物理内存
- 优化所有运行中进程的内存使用
- 显示详细的内存优化结果
- 优化过程中跳过关键系统进程和自身
- 支持中文字符显示

## 需求

- Windows操作系统
- C++编译器（推荐使用Visual Studio）
- Windows SDK

## 编译

1. 在Visual Studio中打开项目
2. 设置适当的构建配置（Debug/Release）
3. 构建解决方案

## 使用方法

1. 运行编译后的可执行文件（建议使用管理员权限）
2. 应用程序将：
   - 显示优化前的内存状态
   - 执行内存优化
   - 显示优化后的内存状态
   - 显示释放的内存量

## 工作原理

该应用程序使用Windows API函数来：

1. 使用`GlobalMemoryStatusEx`检索系统内存信息
2. 使用`CreateToolhelp32Snapshot`枚举正在运行的进程
3. 使用`SetProcessWorkingSetSize`调整进程工作集
4. 计算并显示内存优化结果

优化过程中会跳过关键系统进程（PID 0和4）和应用程序本身，以防止系统不稳定。

## 注意事项

内存优化结果可能因系统配置、运行的进程和当前内存使用情况而异。为获得最佳效果，应用程序应以管理员权限运行。
