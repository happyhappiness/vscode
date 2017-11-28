static void
peerGetSomeNeighbor(ps_state * ps)
{
    StoreEntry *entry = ps->entry;
    HttpRequest *request = ps->request;
    CachePeer *p;
    hier_code code = HIER_NONE;
    assert(entry->ping_status == PING_NONE);

    if (ps->direct == DIRECT_YES) {
        entry->ping_status = PING_DONE;
        return;
    }

#if USE_CACHE_DIGESTS
    if ((p = neighborsDigestSelect(request))) {
        if (neighborType(p, request) == PEER_PARENT)
            code = CD_PARENT_HIT;
        else
            code = CD_SIBLING_HIT;
    } else
#endif
        if ((p = netdbClosestParent(request))) {
            code = CLOSEST_PARENT;
        } else if (peerSelectIcpPing(request, ps->direct, entry)) {
            debugs(44, 3, "peerSelect: Doing ICP pings");
            ps->ping.start = current_time;
            ps->ping.n_sent = neighborsUdpPing(request,
                                               entry,
                                               peerHandlePingReply,
                                               ps,
                                               &ps->ping.n_replies_expected,
                                               &ps->ping.timeout);

            if (ps->ping.n_sent == 0)
                debugs(44, DBG_CRITICAL, "WARNING: neighborsUdpPing returned 0");
            debugs(44, 3, "peerSelect: " << ps->ping.n_replies_expected <<
                   " ICP replies expected, RTT " << ps->ping.timeout <<
                   " msec");

            if (ps->ping.n_replies_expected > 0) {
                entry->ping_status = PING_WAITING;
                eventAdd("peerPingTimeout",
                         peerPingTimeout,
                         ps,
                         0.001 * ps->ping.timeout,
                         0);
                return;
            }
        }

    if (code != HIER_NONE) {
        assert(p);
        debugs(44, 3, "peerSelect: " << hier_code_str[code] << "/" << p->host);
        peerAddFwdServer(&ps->servers, p, code);
    }

    entry->ping_status = PING_DONE;
}