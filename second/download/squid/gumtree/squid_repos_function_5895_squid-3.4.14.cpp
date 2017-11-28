void
netdbPingSite(const char *hostname)
{
#if USE_ICMP
    netdbEntry *n;

    if ((n = netdbLookupHost(hostname)) != NULL)
        if (n->next_ping_time > squid_curtime)
            return;

    ipcache_nbgethostbyname(hostname, netdbSendPing,
                            new generic_cbdata(xstrdup(hostname)));

#endif
}