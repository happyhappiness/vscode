void
netdbDeleteAddrNetwork(Ip::Address &addr)
{
#if USE_ICMP
    netdbEntry *n = netdbLookupAddr(addr);

    if (n == NULL)
        return;

    debugs(38, 3, "netdbDeleteAddrNetwork: " << n->network);

    netdbRelease(n);
#endif
}