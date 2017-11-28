int
netdbHostRtt(const char *host)
{
#if USE_ICMP
    netdbEntry *n = netdbLookupHost(host);

    if (n) {
        n->last_use_time = squid_curtime;
        return (int) (n->rtt + 0.5);
    }

#endif
    return 0;
}