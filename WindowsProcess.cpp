#include "stdafx.h"
#include "WindowsProcess.h"


WindowsProcess::WindowsProcess() :hChildStdinWrite(NULL), hChildStdoutRead(NULL)
{
	ZeroMemory(&piProcInfo, sizeof(piProcInfo));
}
WindowsProcess::~WindowsProcess()
{
	// �ȴ��ӽ��̽���
	WaitForSingleObject(piProcInfo.hProcess, INFINITE);

	// �رչܵ����
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

	// ��������ܵ�
	if (!CreatePipe(&hChildStdinRead, &hChildStdinWrite, &saAttr, 0)) {
		std::cerr << "Error creating input pipe. Error code: " << GetLastError() << std::endl;
		return FALSE;
	}

	// ��������ܵ�
	if (!CreatePipe(&hChildStdoutRead, &hChildStdoutWrite, &saAttr, 0)) {
		std::cerr << "Error creating output pipe. Error code: " << GetLastError() << std::endl;
		return FALSE;
	}

	// �����ӽ���
	STARTUPINFO siStartInfo;

	ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
	siStartInfo.cb = sizeof(STARTUPINFO);
	siStartInfo.hStdError = hChildStdoutWrite;
	siStartInfo.hStdOutput = hChildStdoutWrite;
	siStartInfo.hStdInput = hChildStdinRead;
	siStartInfo.dwFlags |= STARTF_USESTDHANDLES;
	siStartInfo.dwFlags |= STARTF_USESHOWWINDOW;
	siStartInfo.wShowWindow = SW_HIDE;  // ���ش���

	if (!CreateProcess(
		NULL,               // ģ����
		lpExePath,  // ������
		NULL,               // ��ȫ������
		NULL,               // ��ȫ������
		TRUE,               // �̳о��
		0,                  // ������־
		NULL,               // ʹ�ø����̵Ļ�������
		NULL,               // ʹ�ø����̵Ĺ���Ŀ¼
		&siStartInfo,
		&piProcInfo)) {
		std::cerr << "Error creating process. Error code: " << GetLastError() << std::endl;
		return false;
	}

	// �رղ���Ҫ�Ĺܵ����
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
	timeouts.ReadIntervalTimeout = 1000;          // ��ȡ��ʱ
	timeouts.ReadTotalTimeoutMultiplier = 10;   // ��ȡ��ʱ����
	timeouts.ReadTotalTimeoutConstant = 100;    // ��ȡ��ʱ����

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