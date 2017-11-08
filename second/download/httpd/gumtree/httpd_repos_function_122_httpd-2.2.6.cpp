BOOL am_IsComputerConnected(LPSTR szComputerName)
{
    int i = 0;
    while (g_stComputers[i].szComputerName != NULL) {
        if (strcmp(g_stComputers[i].szComputerName, szComputerName) == 0) {
            return TRUE;
        }
        ++i;
    }
    return FALSE;
}