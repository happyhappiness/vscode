                return;
            if (in.EventType == MOUSE_EVENT
                    && (in.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK))
                return;
        }
        remains = ((start + 30) - time(NULL));
        sprintf(count, "%d...",
                (int)remains); /* 30 or less, so can't overflow int */
        if (!SetConsoleCursorPosition(hConErr, coninfo.dwCursorPosition))
            return;
        if (!WriteConsole(hConErr, count, (DWORD)strlen(count), &result, NULL)
                || !result)
            return;
    }
    while ((remains > 0) && WaitForSingleObject(hConIn, 1000) != WAIT_FAILED);
}

static BOOL  die_on_logoff = FALSE;

static LRESULT CALLBACK monitor_service_9x_proc(HWND hWnd, UINT msg,
                                                WPARAM wParam, LPARAM lParam)
{
/* This is the WndProc procedure for our invisible window.
 * When the user shuts down the system, this window is sent
 * a signal WM_ENDSESSION. We clean up by signaling Apache
 * to shut down, and idle until Apache's primary thread quits.
 */
    if ((msg == WM_ENDSESSION)
            && (die_on_logoff || (lParam != ENDSESSION_LOGOFF)))
    {
        ap_signal_parent(SIGNAL_PARENT_SHUTDOWN);
        if (wParam)
            /* Don't leave this message until we are dead! */
            WaitForSingleObject(globdat.mpm_thread, 30000);
        return 0;
    }
    return (DefWindowProc(hWnd, msg, wParam, lParam));
}

static DWORD WINAPI monitor_service_9x_thread(void *service_name)
{
    /* When running as a service under Windows 9x, there is no console
     * window present, and no ConsoleCtrlHandler to call when the system
     * is shutdown.  If the WatchWindow thread is created with a NULL
     * service_name argument, then the ...SystemMonitor window class is
     * used to create the "Apache" window to watch for logoff and shutdown.
     * If the service_name is provided, the ...ServiceMonitor window class
     * is used to create the window named by the service_name argument,
     * and the logoff message is ignored.
     */
    WNDCLASS wc;
    HWND hwndMain;
    MSG msg;

    wc.style         = CS_GLOBALCLASS;
    wc.lpfnWndProc   = monitor_service_9x_proc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = NULL;
    wc.hIcon         = NULL;
    wc.hCursor       = NULL;
    wc.hbrBackground = NULL;
    wc.lpszMenuName  = NULL;
    if (service_name)
        wc.lpszClassName = "ApacheWin95ServiceMonitor";
    else
        wc.lpszClassName = "ApacheWin95SystemMonitor";

    die_on_logoff = service_name ? FALSE : TRUE;

    if (!RegisterClass(&wc))
    {
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, apr_get_os_error(),
                     NULL, "Could not register window class for WatchWindow");
        globdat.service_thread_id = 0;
        return 0;
    }

    /* Create an invisible window */
    hwndMain = CreateWindow(wc.lpszClassName,
                            service_name ? (char *) service_name : "Apache",
                            WS_OVERLAPPEDWINDOW & ~WS_VISIBLE,
                            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                            CW_USEDEFAULT, NULL, NULL, NULL, NULL);

    if (!hwndMain)
    {
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, apr_get_os_error(),
                     NULL, "Could not create WatchWindow");
        globdat.service_thread_id = 0;
        return 0;
    }

    /* If we succeed, eliminate the console window.
     * Signal the parent we are all set up, and
     * watch the message queue while the window lives.
     */
    FreeConsole();
    SetEvent(globdat.service_init);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (msg.message == WM_CLOSE)
            DestroyWindow(hwndMain);
        else {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    globdat.service_thread_id = 0;
    return 0;
}


static BOOL CALLBACK console_control_handler(DWORD ctrl_type)
{
    switch (ctrl_type)
    {
        case CTRL_BREAK_EVENT:
            fprintf(stderr, "Apache server restarting...\n");
