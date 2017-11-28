void
GetProcessName(pid_t pid, char *ProcessName)
{
    HANDLE hProcess;

    strcpy(ProcessName, "unknown");
#if HAVE_WIN32_PSAPI
    /* Get a handle to the process. */
    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
                           PROCESS_VM_READ,
                           FALSE, pid);
    /* Get the process name. */
    if (NULL != hProcess) {
        HMODULE hMod;
        DWORD cbNeeded;

        if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
            GetModuleBaseName(hProcess, hMod, ProcessName, sizeof(ProcessName));
        else {
            CloseHandle(hProcess);
            return;
        }
    } else
        return;
    CloseHandle(hProcess);
#endif
}