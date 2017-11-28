int
neighborUp(const CachePeer * p)
{
    if (!p->tcp_up) {
        peerProbeConnect(const_cast<CachePeer*>(p));
        return 0;
    }

    /*
     * The CachePeer can not be UP if we don't have any IP addresses
     * for it.
     */
    if (0 == p->n_addresses) {
        debugs(15, 8, "neighborUp: DOWN (no-ip): " << p->host << " (" << p->in_addr << ")");
        return 0;
    }

    if (p->options.no_query) {
        debugs(15, 8, "neighborUp: UP (no-query): " << p->host << " (" << p->in_addr << ")");
        return 1;
    }

    if (p->stats.probe_start != 0 &&
            squid_curtime - p->stats.probe_start > Config.Timeout.deadPeer) {
        debugs(15, 8, "neighborUp: DOWN (dead): " << p->host << " (" << p->in_addr << ")");
        return 0;
    }

    debugs(15, 8, "neighborUp: UP: " << p->host << " (" << p->in_addr << ")");
    return 1;
}