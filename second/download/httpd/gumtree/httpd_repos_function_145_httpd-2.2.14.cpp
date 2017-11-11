BOOL RunAndForgetConsole(LPTSTR szCmdLine, BOOL bRedirectConsole)
{
    STARTUPINFO stInfo;
    PROCESS_INFORMATION prInfo;
    BOOL bResult;

    if (bRedirectConsole) {
        return RunRedirectedConsole(szCmdLine);
    }

    memset(&stInfo, 0, sizeof(stInfo));
    stInfo.cb = sizeof(stInfo);
    stInfo.dwFlags = STARTF_USESHOWWINDOW;
    stInfo.wShowWindow = SW_HIDE;

    bResult = CreateProcess(NULL,
                            szCmdLine,
                            NULL,
                            NULL,
                            TRUE,
                            CREATE_NEW_CONSOLE,
                            NULL,
                            NULL,
                            &stInfo,
                            &prInfo);

    if (!bResult) {
        return FALSE;
    }
    if (g_dwOSVersion == OS_VERSION_WIN9X) {
        /* give some time to rescan the status */
        Sleep(2000);
    }
    CloseHandle(prInfo.hThread);
    CloseHandle(prInfo.hProcess);
    return TRUE;
}