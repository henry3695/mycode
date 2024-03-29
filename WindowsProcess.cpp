#include "stdafx.h"
#include "WindowsProcess.h"


WindowsProcess::WindowsProcess() :hChildStdinWrite(NULL), hChildStdoutRead(NULL)
{
	ZeroMemory(&piProcInfo, sizeof(piProcInfo));
}
WindowsProcess::~WindowsProcess()
{
	// 等待子进程结束
	WaitForSingleObject(piProcInfo.hProcess, INFINITE);

	// 关闭管道句柄
	CloseHandle(hChildStdinWrite);
	CloseHandle(hChildStdoutRead);
	CloseHandle(piProcInfo.hProcess);
	CloseHandle(piProcInfo.hThread);


}

BOOL WindowsProcess::Start(LPSTR lpExePath)
{
	SECURITY_ATTRIBUTES saAttr;
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;

	HANDLE hChildStdinRead;
	HANDLE hChildStdoutWrite;

	// 创建输入管道
	if (!CreatePipe(&hChildStdinRead, &hChildStdinWrite, &saAttr, 0)) {
		std::cerr << "Error creating input pipe. Error code: " << GetLastError() << std::endl;
		return FALSE;
	}

	// 创建输出管道
	if (!CreatePipe(&hChildStdoutRead, &hChildStdoutWrite, &saAttr, 0)) {
		std::cerr << "Error creating output pipe. Error code: " << GetLastError() << std::endl;
		return FALSE;
	}

	// 启动子进程
	STARTUPINFO siStartInfo;

	ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
	siStartInfo.cb = sizeof(STARTUPINFO);
	siStartInfo.hStdError = hChildStdoutWrite;
	siStartInfo.hStdOutput = hChildStdoutWrite;
	siStartInfo.hStdInput = hChildStdinRead;
	siStartInfo.dwFlags |= STARTF_USESTDHANDLES;
	siStartInfo.dwFlags |= STARTF_USESHOWWINDOW;
	siStartInfo.wShowWindow = SW_HIDE;  // 隐藏窗口

	if (!CreateProcess(
		NULL,               // 模块名
		lpExePath,  // 命令行
		NULL,               // 安全描述符
		NULL,               // 安全描述符
		TRUE,               // 继承句柄
		0,                  // 创建标志
		NULL,               // 使用父进程的环境变量
		NULL,               // 使用父进程的工作目录
		&siStartInfo,
		&piProcInfo)) {
		std::cerr << "Error creating process. Error code: " << GetLastError() << std::endl;
		return false;
	}

	// 关闭不需要的管道句柄
	CloseHandle(hChildStdinRead);
	CloseHandle(hChildStdoutWrite);
	return TRUE;
}

BOOL WindowsProcess::Write(string inputData, DWORD& bytesWritten)
{
	return WriteFile(hChildStdinWrite, inputData.c_str(), inputData.size(), &bytesWritten, NULL);
}
BOOL  WindowsProcess::Read(string& outData, DWORD& bytesRead)
{
	bytesRead = 0;
	const int bufferSize = 4096;
	char buffer[bufferSize] = { 0 };


	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout = 1000;          // 读取超时
	timeouts.ReadTotalTimeoutMultiplier = 10;   // 读取超时乘数
	timeouts.ReadTotalTimeoutConstant = 100;    // 读取超时常数

	if (!SetCommTimeouts(hChildStdoutRead, &timeouts)) {
		std::cerr << "Error setting timeouts. Error code: " << GetLastError() << std::endl;
		CloseHandle(hChildStdoutRead);
		return FALSE;
	}


	BOOL b = ReadFile(hChildStdoutRead, buffer, bufferSize, &bytesRead, NULL);
	if (b)
	{
		buffer[bytesRead] = 0;
		outData = buffer;
		bytesRead = outData.size();
	}
	return b;
}