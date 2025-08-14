#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// 内存信息结构体
struct MemoryInfo {
	ULONGLONG totalPhys;  // 总物理内存（字节）
	ULONGLONG availPhys;  // 可用物理内存（字节）
};

// 获取系统内存信息
MemoryInfo GetMemoryStatus() {
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	return { memInfo.ullTotalPhys, memInfo.ullAvailPhys };
}

// 格式化内存大小（GB/MB/KB）
string FormatMemory(ULONGLONG bytes) {
	const char* units[] = { "B", "KB", "MB", "GB" };
	int unitIndex = 0;
	double size = bytes;
	
	while (size >= 1024 && unitIndex < 3) {
		size /= 1024;
		unitIndex++;
	}
	
	ostringstream oss;
	oss << fixed << setprecision(2) << size << " " << units[unitIndex];
	return oss.str();
}

// 释放指定进程内存（无任何输出）
void TrimProcessMemory(DWORD pid) {
	HANDLE hProcess = OpenProcess(PROCESS_SET_QUOTA, FALSE, pid);
	if (hProcess == NULL) {
		CloseHandle(hProcess);
		return;
	}
	SetProcessWorkingSetSize(hProcess, (SIZE_T)-1, (SIZE_T)-1);
	CloseHandle(hProcess);
}

// 遍历进程释放内存（无输出）
void TrimAllProcesses() {
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	
	if (hSnapshot == INVALID_HANDLE_VALUE) return;
	
	if (Process32First(hSnapshot, &pe32)) {
		do {
			// 过滤系统关键进程和自身
			if (pe32.th32ProcessID == 0 || pe32.th32ProcessID == 4 || 
				pe32.th32ProcessID == GetCurrentProcessId()) {
				continue;
			}
			TrimProcessMemory(pe32.th32ProcessID);
		} while (Process32Next(hSnapshot, &pe32));
	}
	CloseHandle(hSnapshot);
}

int main() {
	// 确保中文显示
	system("chcp 65001 > nul");
	
	// 优化前内存状态
	MemoryInfo before = GetMemoryStatus();
	cout << "优化前内存状态：" << endl;
	cout << "  总物理内存：" << FormatMemory(before.totalPhys) << endl;
	cout << "  可用物理内存：" << FormatMemory(before.availPhys) << endl << endl;
	
	// 清理缓存（无输出）
	cout << "正在清理系统缓存..." << endl << endl;
	TrimAllProcesses();
	Sleep(1000);  // 等待系统更新内存状态
	
	// 优化后内存状态
	MemoryInfo after = GetMemoryStatus();
	cout << "优化后内存状态：" << endl;
	cout << "  总物理内存：" << FormatMemory(after.totalPhys) << endl;
	cout << "  可用物理内存：" << FormatMemory(after.availPhys) << endl << endl;
	
	// 计算释放内存
	ULONGLONG freedBytes = after.availPhys - before.availPhys;
	double freedPercent = (freedBytes > 0) ? 
	(double)freedBytes / before.totalPhys * 100 : 0.0;
	
	// 显示优化结果
	cout << "===== 优化结果 =====" << endl;
	cout << "  释放内存：" << FormatMemory(freedBytes) << endl;
	cout << "  占总内存比例：" << fixed << setprecision(2) << freedPercent << "%" << endl << endl;
	
	system("pause");
	return 0;
}
