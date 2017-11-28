static void
peerDNSConfigure(const ipcache_addrs *ia, const DnsLookupDetails &, void *data)
{
    peer *p = (peer *)data;

    int j;

    if (p->n_addresses == 0) {
        debugs(15, 1, "Configuring " << neighborTypeStr(p) << " " << p->host << "/" << p->http_port << "/" << p->icp.port);

        if (p->type == PEER_MULTICAST)
            debugs(15, 1, "    Multicast TTL = " << p->mcast.ttl);
    }

    p->n_addresses = 0;

    if (ia == NULL) {
        debugs(0, 0, "WARNING: DNS lookup for '" << p->host << "' failed!");
        return;
    }

    if ((int) ia->count < 1) {
        debugs(0, 0, "WARNING: No IP address found for '" << p->host << "'!");
        return;
    }

    p->tcp_up = p->connect_fail_limit;

    for (j = 0; j < (int) ia->count && j < PEER_MAX_ADDRESSES; j++) {
        p->addresses[j] = ia->in_addrs[j];
        debugs(15, 2, "--> IP address #" << j << ": " << p->addresses[j]);
        p->n_addresses++;
    }

    p->in_addr.SetEmpty();
    p->in_addr = p->addresses[0];
    p->in_addr.SetPort(p->icp.port);

    if (p->type == PEER_MULTICAST)
        peerCountMcastPeersSchedule(p, 10);

#if USE_ICMP
    if (p->type != PEER_MULTICAST)
        if (!p->options.no_netdb_exchange)
            eventAddIsh("netdbExchangeStart", netdbExchangeStart, p, 30.0, 1);
#endif

}