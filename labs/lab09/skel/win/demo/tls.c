#include <stdio.h>
#include <windows.h>

static DWORD dwTlsIndex;

static VOID Foo(VOID)
{
	LPSTR lpThreadArg = TlsGetValue(dwTlsIndex);
	printf("thread_func: arg = %s\n", lpThreadArg);
}

DWORD WINAPI ThreadFunc(LPVOID lpParameter)
{
	TlsSetValue(dwTlsIndex, lpParameter);
	Foo();

	return 0;
}

DWORD main(VOID)
{
	DWORD dwThreadID, dwRet;
	HANDLE hThread1, hThread2;

	setbuf(stdout, NULL);

	dwTlsIndex = TlsAlloc();

	hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadFunc,
		"Thread-1", 0, &dwThreadID);
	hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadFunc,
		"Thread-2", 0, &dwThreadID);

	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE);

	TlsFree(dwTlsIndex);

	return 0;
}
