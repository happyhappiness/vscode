DWORD WINAPI ConsoleWaitingThread(LPVOID lpThreadParameter)
{
    WaitForSingleObject(g_lpRedirectProc.hThread, INFINITE);
    CloseHandle(g_lpRedirectProc.hThread);
    MessageBeep(100);
    g_bConsoleRun = FALSE;
    SetCursor(g_hCursorArrow);
    return 0;
}