static void
peerRefreshDNS(void *data)
{
    peer *p = NULL;

    if (eventFind(peerRefreshDNS, NULL))
        eventDelete(peerRefreshDNS, NULL);

    if (!data && 0 == stat5minClientRequests()) {
        /* no recent client traffic, wait a bit */
        eventAddIsh("peerRefreshDNS", peerRefreshDNS, NULL, 180.0, 1);
        return;
    }

    for (p = Config.peers; p; p = p->next)
        ipcache_nbgethostbyname(p->host, peerDNSConfigure, p);

    /* Reconfigure the peers every hour */
    eventAddIsh("peerRefreshDNS", peerRefreshDNS, NULL, 3600.0, 1);
}