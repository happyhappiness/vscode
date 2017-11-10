void am_ClearComputersSt()
{
    int i;
    for (i = 0; i < MAX_APACHE_COMPUTERS; i++) {
        if (g_stComputers[i].szComputerName) {
            free(g_stComputers[i].szComputerName);
            RegCloseKey(g_stComputers[i].hRegistry);
        }
    }
    memset(g_stComputers, 0, sizeof(ST_MONITORED_COMP) * MAX_APACHE_COMPUTERS);

}