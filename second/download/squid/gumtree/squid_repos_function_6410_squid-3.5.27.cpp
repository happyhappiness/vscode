void
netdbHandlePingReply(const Ip::Address &from, int hops, int rtt)
{
#if USE_ICMP
    netdbEntry *n;
    int N;
    debugs(38, 3, "netdbHandlePingReply: from " << from);

    if ((n = netdbLookupAddr(from)) == NULL)
        return;

    N = ++n->pings_recv;

    if (N > 5)
        N = 5;

    if (rtt < 1)
        rtt = 1;

    n->hops = ((n->hops * (N - 1)) + hops) / N;

    n->rtt = ((n->rtt * (N - 1)) + rtt) / N;

    debugs(38, 3, "netdbHandlePingReply: " << n->network  << "; rtt="<<
           std::setw(5)<< std::setprecision(2) << n->rtt << "  hops="<<
           std::setw(4) << n->hops);

#endif
}