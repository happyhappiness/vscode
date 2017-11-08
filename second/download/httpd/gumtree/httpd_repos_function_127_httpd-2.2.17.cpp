BOOL am_IsComputerConnected(LPTSTR szComputerName)
{
    int i = 0;
    while (g_stComputers[i].szComputerName != NULL) {
        if (_tcscmp(g_stComputers[i].szComputerName, szComputerName) == 0) {
            return TRUE;
        }
        ++i;
    }
    return FALSE;
}