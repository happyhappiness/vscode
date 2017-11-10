BOOL GetApacheServicesStatus()
{
    CHAR szKey[MAX_PATH];
    CHAR achKey[MAX_PATH];
    CHAR szImagePath[MAX_PATH];
    CHAR szBuf[MAX_PATH];
    CHAR szTmp[MAX_PATH];
    HKEY hKey, hSubKey, hKeyRemote;
    DWORD retCode, rv, dwKeyType;
    DWORD dwBufLen = MAX_PATH;
    int i, stPos = 0;
    int computers = 0;

    g_bRescanServices = FALSE;

    am_ClearServicesSt();
    while (g_stComputers[computers].szComputerName != NULL) {
        hKeyRemote = g_stComputers[computers].hRegistry;
        retCode = RegOpenKeyEx(hKeyRemote,
                               "System\\CurrentControlSet\\Services\\",
                               0, KEY_READ, &hKey);
        if (retCode != ERROR_SUCCESS)
        {
            ErrorMessage(NULL, FALSE);
            return FALSE;
        }
        for (i = 0, retCode = ERROR_SUCCESS; retCode == ERROR_SUCCESS; i++)
        {
            retCode = RegEnumKey(hKey, i, achKey, MAX_PATH);
            if (retCode == ERROR_SUCCESS)
            {
                lstrcpy(szKey, "System\\CurrentControlSet\\Services\\");
                lstrcat(szKey, achKey);

                if (RegOpenKeyEx(hKeyRemote, szKey, 0, 
                                 KEY_QUERY_VALUE, &hSubKey) == ERROR_SUCCESS)
                {
                    dwBufLen = MAX_PATH;
                    rv = RegQueryValueEx(hSubKey, "ImagePath", NULL,
                                         &dwKeyType, szImagePath, &dwBufLen);

                    if (rv == ERROR_SUCCESS
                            && (dwKeyType == REG_SZ 
                             || dwKeyType == REG_EXPAND_SZ)
                            && dwBufLen)
                    {
                        lstrcpy(szBuf, szImagePath);
                        CharLower(szBuf);
                        /* the service name could be Apache*.exe */
                        /* the service name could be httpd*.exe or Apache*.exe */
                        if (((strstr(szBuf, "\\apache") != NULL)
                             || (strstr(szBuf, "\\httpd") != NULL))
                                && strstr(szBuf, ".exe") 
                                && (strstr(szBuf, "--ntservice") != NULL 
                                       || strstr(szBuf, "-k ") != NULL))
                        {
                            g_stServices[stPos].szServiceName = strdup(achKey);
                            g_stServices[stPos].szImagePath = 
                                                           strdup(szImagePath);
                            g_stServices[stPos].szComputerName = 
                               strdup(g_stComputers[computers].szComputerName);
                            dwBufLen = MAX_PATH;
                            if (RegQueryValueEx(hSubKey, "Description", NULL,
                                                &dwKeyType, szBuf, &dwBufLen) 
                                    == ERROR_SUCCESS) {
                                g_stServices[stPos].szDescription = 
                                                                 strdup(szBuf);
                            }
                            dwBufLen = MAX_PATH;
                            if (RegQueryValueEx(hSubKey, "DisplayName", NULL,
                                                &dwKeyType, szBuf, &dwBufLen) 
                                    == ERROR_SUCCESS) 
                            {
                                if (strcmp(g_stComputers[computers]
                                        .szComputerName, g_szLocalHost) != 0) 
                                { 
                                    strcpy(szTmp, g_stComputers[computers]
                                                      .szComputerName + 2);
                                    strcat(szTmp, "@");
                                    strcat(szTmp, szBuf);
                                }
                                else {
                                    strcpy(szTmp, szBuf);
                                }
                                g_stServices[stPos].szDisplayName 
                                             