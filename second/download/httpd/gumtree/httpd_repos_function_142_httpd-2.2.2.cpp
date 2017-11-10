BOOL FindRunningServices(void)
{
    int i = 0;
    DWORD dwPid;
    BOOL rv = FALSE;
    while (g_stServices[i].szServiceName != NULL)
    {
        if (!IsServiceRunning(g_stServices[i].szServiceName,
                              g_stServices[i].szComputerName, &dwPid)) {
            dwPid = 0;
        }
        if (g_stServices[i].dwPid != dwPid) {
            rv = TRUE;
        }
        g_stServices[i].dwPid = dwPid;
        ++i;
    }
    return rv;
}