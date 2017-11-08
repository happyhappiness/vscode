static DWORD WINAPI ttyConsoleCtrlThread(LPVOID tty)
{
    WNDCLASS wc;
    MSG msg;
    wc.style         = CS_GLOBALCLASS;
    wc.lpfnWndProc   = ttyConsoleCtrlWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 8;
    wc.hInstance     = NULL;
    wc.hIcon         = NULL;
    wc.hCursor       = NULL;
    wc.hbrBackground = NULL;
    wc.lpszMenuName  = NULL;
    if (((tty_info*)tty)->parent)
        wc.lpszClassName = "ttyConHookChild";
    else
        wc.lpszClassName = "ApacheWin95ServiceMonitor";

    if (!RegisterClass(&wc)) {
#ifdef DBG
        DbgPrintf("A proc %8.8x Error creating class %s (%d)\r\n",
                  GetCurrentProcessId(), wc.lpszClassName, GetLastError());
#endif
        return 0;
    }

    /* Create an invisible window */
    monitor_hwnd = CreateWindow(wc.lpszClassName, ((tty_info*)tty)->name,
                                WS_OVERLAPPED & ~WS_VISIBLE,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                NULL, NULL,
                                ((tty_info*)tty)->instance, tty);

    if (!monitor_hwnd) {
#ifdef DBG
        DbgPrintf("A proc %8.8x Error creating window %s %s (%d)\r\n",
                  GetCurrentProcessId(), wc.lpszClassName,
                  ((tty_info*)tty)->name, GetLastError());
#endif
        return 0;
    }

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    /* Tag again as deleted, just in case we missed WM_DESTROY */
    monitor_hwnd = NULL;
    return 0;
}