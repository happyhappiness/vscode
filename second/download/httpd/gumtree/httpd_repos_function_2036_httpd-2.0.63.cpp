VOID DbgPrintf(
    LPTSTR fmt,
    ...
    )
{
    static HANDLE mutex;
    va_list marker;
    TCHAR szBuf[256];
    DWORD t;
    HANDLE gDbgOut;

    va_start(marker, fmt);
    wvsprintf(szBuf, fmt, marker);
    va_end(marker);

    if (!mutex)
        mutex = CreateMutex(NULL, FALSE, "Win9xConHookDbgOut");
    WaitForSingleObject(mutex, INFINITE);
    gDbgOut = CreateFile("COM1", GENERIC_READ | GENERIC_WRITE, 0,
                         NULL, OPEN_EXISTING, FILE_FLAG_WRITE_THROUGH, NULL);
    WriteFile(gDbgOut, szBuf, strlen(szBuf), &t, NULL);
    CloseHandle(gDbgOut);
    ReleaseMutex(mutex);
}