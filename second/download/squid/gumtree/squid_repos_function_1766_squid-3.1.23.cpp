static int
peerWouldBePinged(const peer * p, HttpRequest * request)
{
    if (p->icp.port == 0)
        return 0;

    if (p->options.no_query)
        return 0;

    if (p->options.mcast_responder)
        return 0;

    if (p->n_addresses == 0)
        return 0;

    if (p->options.background_ping && (squid_curtime - p->stats.last_query < Config.backgroundPingRate))
        return 0;

    /* the case below seems strange, but can happen if the
     * URL host is on the other side of a firewall */
    if (p->type == PEER_SIBLING)
        if (!request->flags.hierarchical)
            return 0;

    if (!peerAllowedToUse(p, request))
        return 0;

    /* Ping dead peers every timeout interval */
    if (squid_curtime - p->stats.last_query > Config.Timeout.deadPeer)
        return 1;

    if (!neighborUp(p))
        return 0;

    return 1;
}