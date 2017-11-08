void am_DisconnectComputer(LPSTR szComputerName)
{
    int i = 0, j;
    while (g_stComputers[i].szComputerName != NULL) {
        if (strcmp(g_stComputers[i].szComputerName, szComputerName) == 0) {
            break;
        }
        ++i;
    }
    if (g_stComputers[i].szComputerName != NULL) {
        free(g_stComputers[i].szComputerName);
        RegCloseKey(g_stComputers[i].hRegistry);
        for (j = i; j < MAX_APACHE_COMPUTERS - 1; j++) {
            g_stComputers[i].szComputerName= g_stComputers[i+1].szComputerName;
            g_stComputers[i].hRegistry = g_stComputers[i+1].hRegistry;
        }
        for (i = j; i < MAX_APACHE_COMPUTERS; i++) {
            g_stComputers[i].szComputerName = NULL;
            g_stComputers[i].hRegistry = NULL;
        }
    }

}