void
netdbHostData(const char *host, int *samp, int *rtt, int *hops)
{
#if USE_ICMP
    netdbEntry *n = netdbLookupHost(host);

    if (n == NULL)
        return;

    *samp = n->pings_recv;

    *rtt = (int) (n->rtt + 0.5);

    *hops = (int) (n->hops + 0.5);

    n->last_use_time = squid_curtime;

#endif
}