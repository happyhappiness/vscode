BOOL RunRedirectedConsole(LPTSTR szCmdLine)
{
    DWORD dwThreadId;
    HANDLE hProc;
    STARTUPINFO stInfo;
    BOOL bResult;

    memset(&stInfo, 0, sizeof(stInfo));
    stInfo.cb = sizeof(stInfo);
    stInfo.dwFlags = STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW;
    stInfo.wShowWindow = SW_HIDE;

    hProc = GetCurrentProcess();

    if (!CreatePipe(&g_hpipeInRead, &g_hpipeInWrite, NULL, MAX_PATH)) {
        ErrorMessage(NULL, TRUE);
    }
    if (!CreatePipe(&g_hpipeOutRead, &g_hpipeOutWrite, NULL, MAX_PATH*8)) {
        ErrorMessage(NULL, TRUE);
    }
    DuplicateHandle(hProc, g_hpipeInRead, hProc, &g_hpipeInRead, 0, TRUE,
                    DUPLICATE_CLOSE_SOURCE|DUPLICATE_SAME_ACCESS);
    DuplicateHandle(hProc, g_hpipeOutWrite, hProc, &g_hpipeOutWrite, 0, TRUE,
                    DUPLICATE_CLOSE_SOURCE|DUPLICATE_SAME_ACCESS);
    DuplicateHandle(hProc, g_hpipeOutWrite, hProc, &g_hpipeStdError, 0, TRUE,
                    DUPLICATE_SAME_ACCESS);
    if (!g_hpipeInRead && !g_hpipeOutWrite && !g_hpipeStdError) {
        ErrorMessage(NULL, TRUE);
    }
    stInfo.hStdInput  = g_hpipeInRead;
    stInfo.hStdOutput = g_hpipeOutWrite;
    stInfo.hStdError  = g_hpipeStdError;

    bResult = CreateProcess(NULL,
        szCmdLine,
        NULL,
        NULL,
        TRUE,
        CREATE_SUSPENDED,
        NULL,
        NULL,
        &stInfo,
        &g_lpRedirectProc);


    CloseHandle(g_hpipeInRead);
    CloseHandle(g_hpipeOutWrite);
    CloseHandle(g_hpipeStdError);

    if (!bResult)
    {
        CloseHandle(g_hpipeInWrite);
        CloseHandle(g_hpipeOutRead);
        CloseHandle(g_hpipeStdError);
        return FALSE;
    }

    CloseHandle(CreateThread(NULL, 0, ConsoleOutputThread,
                             0, 0, &dwThreadId));
    ResumeThread(g_lpRedirectProc.hThread);
    CloseHandle(CreateThread(NULL, 0, ConsoleWaitingThread,
                             0, 0, &dwThreadId));

    return TRUE;
}