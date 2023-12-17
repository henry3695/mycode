#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
using namespace std;
class WindowsProcess
{
	HANDLE hChildStdinWrite;
	HANDLE hChildStdoutRead;
	PROCESS_INFORMATION piProcInfo;
public:
	WindowsProcess();
	~WindowsProcess();
	BOOL Start(LPSTR lpExePath);
	BOOL Write(string inputData, DWORD& bytesWritten);
	BOOL Read(string& outData, DWORD& bytesRead);
};

/*
// 向子进程输入数据
std::string inputData = "ucci\n";
WindowsProcess wpr;
wpr.Start("C:\\mychess\\ELEEYE.EXE");
DWORD bytesWritten;
wpr.Write(inputData, bytesWritten);

string outData;
DWORD bytesRead;
while (wpr.Read(outData, bytesRead))
{
cout << "bytesRead=" << bytesRead << endl;
cout << outData  << endl;
}
*/