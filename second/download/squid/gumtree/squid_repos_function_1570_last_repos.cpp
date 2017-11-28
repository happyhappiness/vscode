static void
dump_peers(StoreEntry * sentry, CachePeer * peers)
{
    char ntoabuf[MAX_IPSTRLEN];
    int i;

    if (peers == NULL)
        storeAppendPrintf(sentry, "There are no neighbors installed.\n");

    for (CachePeer *e = peers; e; e = e->next) {
        assert(e->host != NULL);
        storeAppendPrintf(sentry, "\n%-11.11s: %s\n",
                          neighborTypeStr(e),
                          e->name);
        storeAppendPrintf(sentry, "Host       : %s/%d/%d\n",
                          e->host,
                          e->http_port,
                          e->icp.port);
        storeAppendPrintf(sentry, "Flags      :");
        dump_peer_options(sentry, e);

        for (i = 0; i < e->n_addresses; ++i) {
            storeAppendPrintf(sentry, "Address[%d] : %s\n", i,
                              e->addresses[i].toStr(ntoabuf,MAX_IPSTRLEN) );
        }

        storeAppendPrintf(sentry, "Status     : %s\n",
                          neighborUp(e) ? "Up" : "Down");
        storeAppendPrintf(sentry, "FETCHES    : %d\n", e->stats.fetches);
        storeAppendPrintf(sentry, "OPEN CONNS : %d\n", e->stats.conn_open);
        storeAppendPrintf(sentry, "AVG RTT    : %d msec\n", e->stats.rtt);

        if (!e->options.no_query) {
            storeAppendPrintf(sentry, "LAST QUERY : %8d seconds ago\n",
                              (int) (squid_curtime - e->stats.last_query));

            if (e->stats.last_reply > 0)
                storeAppendPrintf(sentry, "LAST REPLY : %8d seconds ago\n",
                                  (int) (squid_curtime - e->stats.last_reply));
            else
                storeAppendPrintf(sentry, "LAST REPLY : none received\n");

            storeAppendPrintf(sentry, "PINGS SENT : %8d\n", e->stats.pings_sent);

            storeAppendPrintf(sentry, "PINGS ACKED: %8d %3d%%\n",
                              e->stats.pings_acked,
                              Math::intPercent(e->stats.pings_acked, e->stats.pings_sent));
        }

        storeAppendPrintf(sentry, "IGNORED    : %8d %3d%%\n", e->stats.ignored_replies, Math::intPercent(e->stats.ignored_replies, e->stats.pings_acked));

        if (!e->options.no_query) {
            storeAppendPrintf(sentry, "Histogram of PINGS ACKED:\n");
#if USE_HTCP

            if (e->options.htcp) {
                storeAppendPrintf(sentry, "\tMisses\t%8d %3d%%\n",
                                  e->htcp.counts[0],
                                  Math::intPercent(e->htcp.counts[0], e->stats.pings_acked));
                storeAppendPrintf(sentry, "\tHits\t%8d %3d%%\n",
                                  e->htcp.counts[1],
                                  Math::intPercent(e->htcp.counts[1], e->stats.pings_acked));
            } else {
#endif

                for (auto op : WholeEnum<icp_opcode>()) {
                    if (e->icp.counts[op] == 0)
                        continue;

                    storeAppendPrintf(sentry, "    %12.12s : %8d %3d%%\n",
                                      icp_opcode_str[op],
                                      e->icp.counts[op],
                                      Math::intPercent(e->icp.counts[op], e->stats.pings_acked));
                }

#if USE_HTCP

            }

#endif

        }

        if (e->stats.last_connect_failure) {
            storeAppendPrintf(sentry, "Last failed connect() at: %s\n",
                              Time::FormatHttpd(e->stats.last_connect_failure));
        }

        storeAppendPrintf(sentry, "keep-alive ratio: %d%%\n", Math::intPercent(e->stats.n_keepalives_recv, e->stats.n_keepalives_sent));
    }
}