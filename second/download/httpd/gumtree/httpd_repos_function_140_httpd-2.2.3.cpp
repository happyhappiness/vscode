BOOL ApacheManageService(LPCSTR szServiceName, LPCSTR szImagePath,
                         LPSTR szComputerName, DWORD dwCommand)
{
    CHAR szBuf[MAX_PATH];
    CHAR szMsg[MAX_PATH];
    LPSTR sPos;
    BOOL retValue;
    BOOL serviceFlag = TRUE;
    SC_HANDLE schService;
    SC_HANDLE schSCManager;
    SERVICE_STATUS schSStatus;
    int ticks;

    if (g_dwOSVersion == OS_VERSION_WIN9X)
    {
        sPos = strstr(szImagePath, "-k start");
        if (sPos)
        {
            lstrcpyn(szBuf, szImagePath, (int)(sPos - szImagePath));
            switch (dwCommand)
            {
            case SERVICE_CONTROL_STOP:
                lstrcat(szBuf, " -k shutdown -n ");
                break;

            case SERVICE_CONTROL_CONTINUE:
                sprintf(szMsg, g_lpMsg[IDS_MSG_SRVSTART - IDS_MSG_FIRST],
                        szServiceName);
                addListBoxString(g_hwndStdoutList, szMsg);
                lstrcat(szBuf, " -k start -n ");
                serviceFlag = FALSE;
                break;

            case SERVICE_APACHE_RESTART:
                lstrcat(szBuf, " -k restart -n ");
                break;

            default:
                return FALSE;
            }
            lstrcat(szBuf, szServiceName);
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
            sprintf(szMsg, g_lpMsg[IDS_MSG_SRVSTARTED - IDS_MSG_FIRST],
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
            return FALSE;
        }

        schService = OpenService(schSCManager, szServiceName,
                                 SERVICE_QUERY_STATUS | SERVICE_START |
                                 SERVICE_STOP | SERVICE_USER_DEFINED_CONTROL);
        if (schService != NULL)
        {
            retValue = FALSE;
            g_bConsoleRun = TRUE;
            SetCursor(g_hCursorHourglass);
            switch (dwCommand)
            {
            case SERVICE_CONTROL_STOP:
                sprintf(szMsg, g_lpMsg[IDS_MSG_SRVSTOP - IDS_MSG_FIRST],
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
                if (QueryServiceStatus(schService, &schSStatus))
                {
                    if (schSStatus.dwCurrentState == SERVICE_STOPPED)
                    {
                        retValue = TRUE;
                        sprintf(szMsg,
                                g_lpMsg[IDS_MSG_SRVSTOPPED - IDS_MSG_FIRST],
                                szServiceName);
                        addListBoxString(g_hwndStdoutList, szMsg);
                    }
                }
                break;

            case SERVICE_CONTROL_CONTINUE:
                sprintf(szMsg, g_lpMsg[IDS_MSG_SRVSTART - IDS_MSG_FIRST],
                        szServiceName);
                addListBoxString(g_hwndStdoutList, szMsg);

                if (StartService(schService, 0, NULL))
                {
            