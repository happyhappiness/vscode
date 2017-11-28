void
netdbUpdatePeer(HttpRequest * r, peer * e, int irtt, int ihops)
{
#if USE_ICMP
    netdbEntry *n;
    double rtt = (double) irtt;
    double hops = (double) ihops;
    net_db_peer *p;
    debugs(38, 3, "netdbUpdatePeer: '" << r->GetHost() << "', " << ihops << " hops, " << irtt << " rtt");
    n = netdbLookupHost(r->GetHost());

    if (n == NULL) {
        debugs(38, 3, "netdbUpdatePeer: host '" << r->GetHost() << "' not found");
        return;
    }

    if ((p = netdbPeerByName(n, e->host)) == NULL)
        p = netdbPeerAdd(n, e);

    p->rtt = rtt;

    p->hops = hops;

    p->expires = squid_curtime + 3600;

    if (n->n_peers < 2)
        return;

    qsort((char *) n->peers,
          n->n_peers,
          sizeof(net_db_peer),
          sortPeerByRtt);

#endif
}