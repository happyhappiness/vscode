void am_DisconnectComputer(LPTSTR szComputerName)
{
    int i = 0, j;
    while (g_stComputers[i].szComputerName != NULL) {
        if (_tcscmp(g_stComputers[i].szComputerName, szComputerName) == 0) {
            break;
        }
        ++i;
    }
    if (g_stComputers[i].szComputerName != NULL) {
        free(g_stComputers[i].szComputerName);
        RegCloseKey(g_stComputers[i].hRegistry);
        for (j = i; j < MAX_APACHE_COMPUTERS - 1; j++) {
            g_stComputers[j].szComputerName= g_stComputers[j+1].szComputerName;
            g_stComputers[j].hRegistry = g_stComputers[j+1].hRegistry;
        }
        g_stComputers[j].szComputerName = NULL;
        g_stComputers[j].hRegistry = NULL;
    }
}