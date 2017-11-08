BOOL IsServiceRunning(LPCTSTR szServiceName, LPCTSTR szComputerName,
                      LPDWORD lpdwPid)
{
    DWORD dwPid;
    HWND hWnd;
    SC_HANDLE schService;
    SC_HANDLE schSCManager;
    SERVICE_STATUS schSStatus;

    if (g_dwOSVersion == OS_VERSION_WIN9X)
    {
        hWnd = FindWindow(_T("ApacheWin95ServiceMonitor"), szServiceName);
        if (hWnd && GetWindowThreadProcessId(hWnd, &dwPid))
        {
            *lpdwPid = 1;
            return TRUE;
        }
        else {
            return FALSE;
        }
    }
    else
    {
        dwPid = 0;
        schSCManager = OpenSCManager(szComputerName, NULL,
                                     SC_MANAGER_CONNECT);
        if (!schSCManager) {
            return FALSE;
        }

        schService = OpenService(schSCManager, szServiceName,
                                 SERVICE_QUERY_STATUS);
        if (schService != NULL)
        {
            if (QueryServiceStatus(schService, &schSStatus))
            {
                dwPid = schSStatus.dwCurrentState;
                if (lpdwPid) {
                    *lpdwPid = 1;
                }
            }
            CloseServiceHandle(schService);
            CloseServiceHandle(schSCManager);
            return dwPid == SERVICE_RUNNING ? TRUE : FALSE;
        }
        else {
            g_bRescanServices = TRUE;
        }
        CloseServiceHandle(schSCManager);
        return FALSE;

    }

    return FALSE;
}