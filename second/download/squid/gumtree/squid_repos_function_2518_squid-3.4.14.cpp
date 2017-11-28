void
start_announce(void *datanotused)
{
    if (0 == Config.onoff.announce)
        return;

    if (!Comm::IsConnOpen(icpOutgoingConn))
        return;

    ipcache_nbgethostbyname(Config.Announce.host, send_announce, NULL);

    eventAdd("send_announce", start_announce, NULL, (double) Config.Announce.period, 1);
}