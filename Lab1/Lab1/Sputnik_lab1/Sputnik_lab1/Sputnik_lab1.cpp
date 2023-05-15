#include <iostream>
#include <windows.h>

void debug(int pid) {

    DebugActiveProcess(pid);
    int temp = 0;

    DEBUG_EVENT DBEvent;

    while (1)
    {
        WaitForDebugEvent(&DBEvent, INFINITE);
        ContinueDebugEvent(pid, DBEvent.dwThreadId, DBG_CONTINUE);
    }
}

int main()
{

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    wchar_t cmdLine[] = L"./lab1.exe";

    if (CreateProcess(
        cmdLine, NULL,
        NULL, NULL,
        TRUE, NULL,
        NULL, NULL,
        &si, &pi)) {
        std::cout << "Create Process succes!" << std::endl;
        std::cout << "Create Process pid = " << std::dec << pi.dwProcessId << std::endl;
    }
    else {
        std::cout << "Create Process failed!" << std::endl;
    }
    setlocale(LC_ALL, "rus");
    debug(pi.dwProcessId);
}