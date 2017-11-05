int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    TCHAR szTmp[MAX_LOADSTRING];
    TCHAR szCmp[MAX_COMPUTERNAME_LENGTH+4];
    MSG msg;
    /* existing window */
    HWND appwindow;
    DWORD dwControl;
    int i;
    DWORD d;

    if (!GetSystemOSVersion(&g_dwOSVersion))
    {
        ErrorMessage(NULL, TRUE);
        return 1;
    }

    g_LangID = GetUserDefaultLangID();
    if ((g_LangID & 0xFF) != LANG_ENGLISH) {
        g_LangID = MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);
    }
    for (i = IDS_MSG_FIRST; i <= IDS_MSG_LAST; ++i) {
        LoadString(hInstance, i, szTmp, MAX_LOADSTRING);
        g_lpMsg[i - IDS_MSG_FIRST] = _tcsdup(szTmp);
    }
    LoadString(hInstance, IDS_APMONITORTITLE, szTmp, MAX_LOADSTRING);
    d = MAX_COMPUTERNAME_LENGTH+1;
    _tcscpy(szCmp, _T("\\\\"));
    GetComputerName(szCmp + 2, &d);
    _tcsupr(szCmp);
    g_szLocalHost = _tcsdup(szCmp);

    memset(g_stComputers, 0, sizeof(ST_MONITORED_COMP) * MAX_APACHE_COMPUTERS);
    g_stComputers[0].szComputerName = _tcsdup(szCmp);
    g_stComputers[0].hRegistry = HKEY_LOCAL_MACHINE;
    g_szTitle = _tcsdup(szTmp);
    LoadString(hInstance, IDS_APMONITORCLASS, szTmp, MAX_LOADSTRING);
    g_szWindowClass = _tcsdup(szTmp);

    appwindow = FindWindow(g_szWindowClass, g_szTitle);

#ifdef UNICODE
    __wargv = CommandLineToArgvW(GetCommandLineW(), &__argc);
#else
    _setargv();
#endif

    if ((__argc == 2) && (_tcscmp(__targv[1], _T("--kill")) == 0))
    {
        /* Off to chase and close up every ApacheMonitor taskbar window */
        return KillAllMonitors();
    }
    else if ((__argc == 4) && (g_dwOSVersion >= OS_VERSION_WIN2K))
    {
        dwControl = _ttoi(__targv[1]);
        if ((dwControl != SERVICE_CONTROL_CONTINUE) &&
            (dwControl != SERVICE_APACHE_RESTART) &&
            (dwControl != SERVICE_CONTROL_STOP))
        {
            return 1;
        }

        /* Chase down and close up our session's previous window */
        if ((appwindow) != NULL)
            KillAWindow(appwindow);
    }
    else if (__argc != 1) {
        return 1;
    }
    else if (appwindow)
    {
        ErrorMessage(g_lpMsg[IDS_MSG_APPRUNNING - IDS_MSG_FIRST], FALSE);
        return 0;
    }

    g_icoStop          = LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICOSTOP),
                                   IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
    g_icoRun           = LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICORUN),
                                   IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
    g_hCursorHourglass = LoadImage(NULL, MAKEINTRESOURCE(OCR_WAIT),
                                   IMAGE_CURSOR, LR_DEFAULTSIZE,
                                   LR_DEFAULTSIZE, LR_SHARED);
    g_hCursorArrow     = LoadImage(NULL, MAKEINTRESOURCE(OCR_NORMAL),
                                   IMAGE_CURSOR, LR_DEFAULTSIZE,
                                   LR_DEFAULTSIZE, LR_SHARED);
    g_hBmpStart        = LoadImage(hInstance, MAKEINTRESOURCE(IDB_BMPRUN),
                                   IMAGE_BITMAP, XBITMAP, YBITMAP,
                                   LR_DEFAULTCOLOR);
    g_hBmpStop         = LoadImage(hInstance, MAKEINTRESOURCE(IDB_BMPSTOP),
                                   IMAGE_BITMAP, XBITMAP, YBITMAP,
                                   LR_DEFAULTCOLOR);

    memset(g_stServices, 0, sizeof(ST_APACHE_SERVICE) * MAX_APACHE_SERVICES);
    CoInitialize(NULL);
    InitCommonControls();
    g_hInstance = hInstance;
    g_hwndMain = CreateMainWindow(hInstance);
    g_bUiTaskbarCreated = RegisterWindowMessage(_T("TaskbarCreated"));
    InitializeCriticalSection(&g_stcSection);
    g_hwndServiceDlg = NULL;
    if (g_hwndMain != NULL)
    {
        /* To avoid recursion, pass ImagePath NULL (a noop on NT and later) */
        if ((__argc == 4) && (g_dwOSVersion >= OS_VERSION_WIN2K))
            ApacheManageService(__targv[2], NULL, __targv[3], dwControl);

        while (GetMessage(&msg, NULL, 0, 0) == TRUE)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        am_ClearServicesSt();
    }
    am_ClearComputersSt();
    DeleteCriticalSection(&g_stcSection);
    DestroyIcon(g_icoStop);
    DestroyIcon(g_icoRun);
    DestroyCursor(g_hCursorHourglass);
    DestroyCursor(g_hCursorArrow);
    DeleteObject(g_hBmpStart);
    DeleteObject(g_hBmpStop);
    CoUninitialize();
    return 0;
}