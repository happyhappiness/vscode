BOOL ApacheManageService(LPCTSTR szServiceName, LPCTSTR szImagePath,
                         LPTSTR szComputerName, DWORD dwCommand)
{
    TCHAR szBuf[MAX_PATH];
    TCHAR szMsg[MAX_PATH];
    LPTSTR sPos;
    BOOL retValue;
    BOOL serviceFlag = TRUE;
    SC_HANDLE schService;
    SC_HANDLE schSCManager;
    SERVICE_STATUS schSStatus;
    int ticks;

    if (g_dwOSVersion == OS_VERSION_WIN9X)
    {
        sPos = _tcsstr(szImagePath, _T("-k start"));
        if (sPos)
        {
            _tcsncpy(szBuf, szImagePath, (int)(sPos - szImagePath));
            switch (dwCommand)
            {
            case SERVICE_CONTROL_STOP:
                _tcscat(szBuf, _T(" -k shutdown -n "));
                break;

            case SERVICE_CONTROL_CONTINUE:
                _sntprintf(szMsg, sizeof(szMsg) / sizeof(TCHAR),
                          g_lpMsg[IDS_MSG_SRVSTART - IDS_MSG_FIRST],
                          szServiceName);
                addListBoxString(g_hwndStdoutList, szMsg);
                _tcscat(szBuf, _T(" -k start -n "));
                serviceFlag = FALSE;
                break;

            case SERVICE_APACHE_RESTART:
                _tcscat(szBuf, _T(" -k restart -n "));
                break;

            default:
                return FALSE;
            }
            _tcscat(szBuf, szServiceName);
        }
        else {
            return FALSE;
        }
        g_bConsoleRun = TRUE;
        SetCursor(g_hCursorHourglass);
        if (!RunAndForgetConsole(szBuf, serviceFlag))
        {
            ErrorMessage(NULL, FALSE);
            g_bConsoleRun = FALSE;
            SetCursor(g_hCursorArrow);
            return FALSE;
        }
        else if (!serviceFlag)
        {
            _sntprintf(szMsg, sizeof(szMsg) / sizeof(TCHAR), 
                      g_lpMsg[IDS_MSG_SRVSTARTED - IDS_MSG_FIRST],
                      szServiceName);
            addListBoxString(g_hwndStdoutList, szMsg);
            g_bConsoleRun = FALSE;
            SetCursor(g_hCursorArrow);
            return TRUE;
        }
    }
    else
    {
        schSCManager = OpenSCManager(szComputerName, NULL,
                                     SC_MANAGER_CONNECT);
        if (!schSCManager) {
            ErrorMessage(g_lpMsg[IDS_MSG_SRVFAILED - IDS_MSG_FIRST],
                         FALSE);
            return FALSE;
        }

        schService = OpenService(schSCManager, szServiceName,
                                 SERVICE_QUERY_STATUS | SERVICE_START |
                                 SERVICE_STOP | SERVICE_USER_DEFINED_CONTROL);
        if (schService == NULL)
        {
            /* Avoid recursion of ImagePath NULL (from this Respawn) */
            if (szImagePath) {
                am_RespawnAsUserAdmin(g_hwndMain, dwCommand, 
                                      szServiceName, szComputerName);
            }
            else {
                ErrorMessage(g_lpMsg[IDS_MSG_SRVFAILED - IDS_MSG_FIRST],
                             FALSE);
            }
            CloseServiceHandle(schSCManager);
            return FALSE;
        }
        else
        {
            retValue = FALSE;
            g_bConsoleRun = TRUE;
            SetCursor(g_hCursorHourglass);
            switch (dwCommand)
            {
            case SERVICE_CONTROL_STOP:
                _sntprintf(szMsg, sizeof(szMsg) / sizeof(TCHAR), 
                          g_lpMsg[IDS_MSG_SRVSTOP - IDS_MSG_FIRST],
                          szServiceName);
                addListBoxString(g_hwndStdoutList, szMsg);
                if (ControlService(schService, SERVICE_CONTROL_STOP,
                                   &schSStatus)) {
                    Sleep(1000);
                    while (QueryServiceStatus(schService, &schSStatus))
                    {
                        if (schSStatus.dwCurrentState == SERVICE_STOP_PENDING)
                        {
                            Sleep(1000);
                        }
                        else {
                            break;
                        }
                    }
                }
       