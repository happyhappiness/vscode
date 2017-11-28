void
wccpInit(void)
{
    debugs(80, 5, "wccpInit: Called");
    memset(&wccp_here_i_am, '\0', sizeof(wccp_here_i_am));
    wccp_here_i_am.type = htonl(WCCP_HERE_I_AM);
    wccp_here_i_am.version = htonl(Config.Wccp.version);
    wccp_here_i_am.revision = htonl(WCCP_REVISION);
    last_change = 0;
    last_id = 0;
    last_assign_buckets_change = 0;
    number_caches = 0;

    if (!Config.Wccp.router.IsAnyAddr())
        if (!eventFind(wccpHereIam, NULL))
            eventAdd("wccpHereIam", wccpHereIam, NULL, 5.0, 1);
}