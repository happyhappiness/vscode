void
netdbExchangeUpdatePeer(Ip::Address &addr, CachePeer * e, double rtt, double hops)
{
#if USE_ICMP
    netdbEntry *n;
    net_db_peer *p;
    debugs(38, 5, "netdbExchangeUpdatePeer: '" << addr << "', "<<
           std::setfill('0')<< std::setprecision(2) << hops << " hops, " <<
           rtt << " rtt");

    if ( !addr.isIPv4() ) {
        debugs(38, 5, "netdbExchangeUpdatePeer: Aborting peer update for '" << addr << "', NetDB cannot handle IPv6.");
        return;
    }

    n = netdbLookupAddr(addr);

    if (n == NULL)
        n = netdbAdd(addr);

    assert(NULL != n);

    if ((p = netdbPeerByName(n, e->host)) == NULL)
        p = netdbPeerAdd(n, e);

    p->rtt = rtt;

    p->hops = hops;

    p->expires = squid_curtime + 3600;	/* XXX ? */

    if (n->n_peers < 2)
        return;

    qsort((char *) n->peers,
          n->n_peers,
          sizeof(net_db_peer),
          sortPeerByRtt);

#endif
}