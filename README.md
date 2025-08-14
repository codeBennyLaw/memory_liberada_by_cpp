# MemoryLiberada

[![Language](https://img.shields.io/badge/Language-English-blue.svg)](README.md) [![Language](https://img.shields.io/badge/语言-中文-red.svg)](README_zh.md)

A Windows application to optimize system memory usage by trimming working sets of running processes.

## Overview

MemoryLiberada is a C++ application that helps free up system memory by trimming the working set of running processes. It displays memory status before and after optimization, showing the amount of memory freed.

The application works by calling `SetProcessWorkingSetSize` with special parameters that tell Windows to trim the working set of each process, which can help free up physical memory.

## Features

- Displays total and available physical memory
- Optimizes memory usage across running processes
- Shows detailed memory optimization results
- Skips critical system processes and itself during optimization
- Supports Chinese character display

## Requirements

- Windows operating system
- C++ compiler (Visual Studio recommended)
- Windows SDK

## Compilation

1. Open the project in Visual Studio
2. Set the appropriate build configuration (Debug/Release)
3. Build the solution

## Usage

1. Run the compiled executable (administrator privileges recommended)
2. The application will:
   - Display memory status before optimization
   - Perform memory optimization
   - Display memory status after optimization
   - Show the amount of memory freed

## How It Works

The application uses Windows API functions to:

1. Retrieve system memory information using `GlobalMemoryStatusEx`
2. Enumerate running processes with `CreateToolhelp32Snapshot`
3. Trim process working sets using `SetProcessWorkingSetSize`
4. Calculate and display memory optimization results

Critical system processes (PID 0 and 4) and the application itself are skipped during optimization to prevent system instability.

## Note

Memory optimization results may vary depending on system configuration, running processes, and current memory usage. The application should be run with administrator privileges for best results.
