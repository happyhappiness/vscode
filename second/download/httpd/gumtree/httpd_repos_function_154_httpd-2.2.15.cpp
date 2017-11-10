static int KillAllMonitors(void)
{
    HWND appwindow;
    int exitcode = 0;
    PWTS_PROCESS_INFO tsProcs;
    DWORD tsProcCount, i;
    DWORD thisProcId; 

    /* This is graceful, close our own Window, clearing the icon */
    if ((appwindow = FindWindow(g_szWindowClass, g_szTitle)) != NULL)
        exitcode = KillAWindow(appwindow);

    if (g_dwOSVersion < OS_VERSION_WIN2K)
        return exitcode;

    thisProcId = GetCurrentProcessId();

    if (!WTSEnumerateProcesses(WTS_CURRENT_SERVER_HANDLE, 0, 1,
                               &tsProcs, &tsProcCount))
        return exitcode;

    /* This is ungraceful; close other Windows, with a lingering icon.
     * Since on terminal server it's not possible to post the message
     * to exit across sessions, we have to suffer this side effect
     * of a taskbar 'icon' which will evaporate the next time that
     * the user hovers over it or when the taskbar area is updated.
     */
    for (i = 0; i < tsProcCount; ++i) {
        if (_tcscmp(tsProcs[i].pProcessName, _T(AM_STRINGIFY(BIN_NAME))) == 0
                && tsProcs[i].ProcessId != thisProcId)
            WTSTerminateProcess(WTS_CURRENT_SERVER_HANDLE, 
                                tsProcs[i].ProcessId, 1);
    }
    WTSFreeMemory(tsProcs);
    return exitcode;
}