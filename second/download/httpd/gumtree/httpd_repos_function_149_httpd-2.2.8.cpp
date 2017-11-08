int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    CHAR szTmp[MAX_LOADSTRING];
    CHAR szCmp[MAX_COMPUTERNAME_LENGTH+4];
    MSG msg;
    /* single instance mutex */
    HANDLE hMutex;
    int i;
    DWORD d;

    g_LangID = GetUserDefaultLangID();
    if ((g_LangID & 0xFF) != LANG_ENGLISH) {
        g_LangID = MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);
    }
    for (i = IDS_MSG_FIRST; i <= IDS_MSG_LAST; ++i) {
        LoadString(hInstance, i, szTmp, MAX_LOADSTRING);
        g_lpMsg[i - IDS_MSG_FIRST] = strdup(szTmp);
    }
    LoadString(hInstance, IDS_APMONITORTITLE, szTmp, MAX_LOADSTRING);
    d = MAX_COMPUTERNAME_LENGTH+1;
    strcpy(szCmp, "\\\\");
    GetComputerName(szCmp + 2, &d);
    strupr(szCmp);
    g_szLocalHost = strdup(szCmp);

    memset(g_stComputers, 0, sizeof(ST_MONITORED_COMP) * MAX_APACHE_COMPUTERS);
    g_stComputers[0].szComputerName = strdup(szCmp);
    g_stComputers[0].hRegistry = HKEY_LOCAL_MACHINE;
    g_szTitle = strdup(szTmp);
    LoadString(hInstance, IDS_APMONITORCLASS, szTmp, MAX_LOADSTRING);
    g_szWindowClass = strdup(szTmp);

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

    hMutex = CreateMutex(NULL, FALSE, "APSRVMON_MUTEX");
    if ((hMutex == NULL) || (GetLastError() == ERROR_ALREADY_EXISTS))
    {
        ErrorMessage(g_lpMsg[IDS_MSG_APPRUNNING - IDS_MSG_FIRST], FALSE);
        if (hMutex) {
            CloseHandle(hMutex);
        }
        return 0;
    }

    memset(g_stServices, 0, sizeof(ST_APACHE_SERVICE) * MAX_APACHE_SERVICES);
    CoInitialize(NULL);
    InitCommonControls();
    g_hInstance = hInstance;
    g_hwndMain = CreateMainWindow(hInstance);
    g_bUiTaskbarCreated = RegisterWindowMessage("TaskbarCreated");
    InitializeCriticalSection(&g_stcSection);
    g_hwndServiceDlg = NULL;
    if (g_hwndMain != NULL)
    {
        while (GetMessage(&msg, NULL, 0, 0) == TRUE)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        am_ClearServicesSt();
    }
    am_ClearComputersSt();
    DeleteCriticalSection(&g_stcSection);
    CloseHandle(hMutex);
    DestroyIcon(g_icoStop);
    DestroyIcon(g_icoRun);
    DestroyCursor(g_hCursorHourglass);
    DestroyCursor(g_hCursorArrow);
    DeleteObject(g_hBmpStart);
    DeleteObject(g_hBmpStop);
    CoUninitialize();
    return 0;
}