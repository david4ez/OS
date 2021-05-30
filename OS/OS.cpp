#include <iostream>
#include <Windows.h>

using namespace std;

BOOL Is64Bit() {
#if defined(_WIN64)
    return TRUE;
#elif defined(_WIN32)
    BOOL f64 = FALSE;
    return IsWow64Process(GetCurrentProcess(), &f64) && f64;
#else
    return FALSE;
#endif
}

int main() {
    NTSTATUS(WINAPI* RtlGetVersion)(LPOSVERSIONINFOEXW);

    OSVERSIONINFOEXW osInfo;

    *(FARPROC*)&RtlGetVersion = GetProcAddress(GetModuleHandleA("ntdll"), "RtlGetVersion");

    if (NULL != RtlGetVersion) {
        osInfo.dwOSVersionInfoSize = sizeof(osInfo);
        RtlGetVersion(&osInfo);

        cout << "Operating System: Windows " << osInfo.dwMajorVersion
             << (Is64Bit() ? " x64" : " x32")
             << " (Build " << osInfo.dwBuildNumber << "), " 
             << "Service Pack " << osInfo.wServicePackMajor << endl;
    }

    system("pause");

    return 0;
}