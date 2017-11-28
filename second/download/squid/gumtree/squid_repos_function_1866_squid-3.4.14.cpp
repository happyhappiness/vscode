int
neighborsUdpPing(HttpRequest * request,
                 StoreEntry * entry,
                 IRCB * callback,
                 void *callback_data,
                 int *exprep,
                 int *timeout)
{
    const char *url = entry->url();
    MemObject *mem = entry->mem_obj;
    CachePeer *p = NULL;
    int i;
    int reqnum = 0;
    int flags;
    icp_common_t *query;
    int queries_sent = 0;
    int peers_pinged = 0;
    int parent_timeout = 0, parent_exprep = 0;
    int sibling_timeout = 0, sibling_exprep = 0;
    int mcast_timeout = 0, mcast_exprep = 0;

    if (Config.peers == NULL)
        return 0;

    assert(entry->swap_status == SWAPOUT_NONE);

    mem->start_ping = current_time;

    mem->ping_reply_callback = callback;

    mem->ircb_data = callback_data;

    reqnum = icpSetCacheKey((const cache_key *)entry->key);

    for (i = 0, p = first_ping; i++ < Config.npeers; p = p->next) {
        if (p == NULL)
            p = Config.peers;

        debugs(15, 5, "neighborsUdpPing: Peer " << p->host);

        if (!peerWouldBePinged(p, request))
            continue;		/* next CachePeer */

        ++peers_pinged;

        debugs(15, 4, "neighborsUdpPing: pinging peer " << p->host << " for '" << url << "'");

        debugs(15, 3, "neighborsUdpPing: key = '" << entry->getMD5Text() << "'");

        debugs(15, 3, "neighborsUdpPing: reqnum = " << reqnum);

#if USE_HTCP
        if (p->options.htcp && !p->options.htcp_only_clr) {
            if (Config.Port.htcp <= 0) {
                debugs(15, DBG_CRITICAL, "HTCP is disabled! Cannot send HTCP request to peer.");
                continue;
            }

            debugs(15, 3, "neighborsUdpPing: sending HTCP query");
            if (htcpQuery(entry, request, p) <= 0)
                continue; // unable to send.
        } else
#endif
        {
            if (Config.Port.icp <= 0 || !Comm::IsConnOpen(icpOutgoingConn)) {
                debugs(15, DBG_CRITICAL, "ICP is disabled! Cannot send ICP request to peer.");
                continue;
            } else {

                if (p->type == PEER_MULTICAST)
                    mcastSetTtl(icpOutgoingConn->fd, p->mcast.ttl);

                if (p->icp.port == echo_port) {
                    debugs(15, 4, "neighborsUdpPing: Looks like a dumb cache, send DECHO ping");
                    query = _icp_common_t::createMessage(ICP_DECHO, 0, url, reqnum, 0);
                    icpUdpSend(icpOutgoingConn->fd, p->in_addr, query, LOG_ICP_QUERY, 0);
                } else {
                    flags = 0;

                    if (Config.onoff.query_icmp)
                        if (p->icp.version == ICP_VERSION_2)
                            flags |= ICP_FLAG_SRC_RTT;

                    query = _icp_common_t::createMessage(ICP_QUERY, flags, url, reqnum, 0);

                    icpUdpSend(icpOutgoingConn->fd, p->in_addr, query, LOG_ICP_QUERY, 0);
                }
            }
        }

        ++queries_sent;

        ++ p->stats.pings_sent;

        if (p->type == PEER_MULTICAST) {
            mcast_exprep += p->mcast.n_replies_expected;
            mcast_timeout += (p->stats.rtt * p->mcast.n_replies_expected);
        } else if (neighborUp(p)) {
            /* its alive, expect a reply from it */

            if (neighborType(p, request) == PEER_PARENT) {
                ++parent_exprep;
                parent_timeout += p->stats.rtt;
            } else {
                ++sibling_exprep;
                sibling_timeout += p->stats.rtt;
            }
        } else {
            /* Neighbor is dead; ping it anyway, but don't expect a reply */
            /* log it once at the threshold */

            if (p->stats.logged_state == PEER_ALIVE) {
                debugs(15, DBG_IMPORTANT, "Detected DEAD " << neighborTypeStr(p) << ": " << p->name);
                p->stats.logged_state = PEER_DEAD;
            }
        }

        p->stats.last_query = squid_curtime;

        /*
         * keep probe_start == 0 for a multicast CachePeer,
         * so neighborUp() never says this CachePeer is dead.
         */

        if ((p->type != PEER_MULTICAST) && (p->stats.probe_start == 0))
            p->stats.probe_start = squid_curtime;
    }

    if ((first_ping = first_ping->next) == NULL)
        first_ping = Config.peers;

    /*
     * How many replies to expect?
     */
    *exprep = parent_exprep + sibling_exprep + mcast_exprep;

    /*
     * If there is a configured timeout, use it
     */
    if (Config.Timeout.icp_query)
        *timeout = Config.Timeout.icp_query;
    else {
        if (*exprep > 0) {
            if (parent_exprep)
                *timeout = 2 * parent_timeout / parent_exprep;
            else if (mcast_exprep)
                *timeout = 2 * mcast_timeout / mcast_exprep;
            else
                *timeout = 2 * sibling_timeout / sibling_exprep;
        } else
            *timeout = 2000;	/* 2 seconds */

        if (Config.Timeout.icp_query_max)
            if (*timeout > Config.Timeout.icp_query_max)
                *timeout = Config.Timeout.icp_query_max;

        if (*timeout < Config.Timeout.icp_query_min)
            *timeout = Config.Timeout.icp_query_min;
    }

    return peers_pinged;
}