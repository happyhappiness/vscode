CachePeer *
getWeightedRoundRobinParent(HttpRequest * request)
{
    CachePeer *p;
    CachePeer *q = NULL;
    int weighted_rtt;

    for (p = Config.peers; p; p = p->next) {
        if (!p->options.weighted_roundrobin)
            continue;

        if (neighborType(p, request->url) != PEER_PARENT)
            continue;

        if (!peerHTTPOkay(p, request))
            continue;

        if (q && q->rr_count < p->rr_count)
            continue;

        q = p;
    }

    if (q && q->rr_count > 1000000)
        for (p = Config.peers; p; p = p->next) {
            if (!p->options.weighted_roundrobin)
                continue;

            if (neighborType(p, request->url) != PEER_PARENT)
                continue;

            p->rr_count = 0;
        }

    if (q) {
        weighted_rtt = (q->stats.rtt - q->basetime) / q->weight;

        if (weighted_rtt < 1)
            weighted_rtt = 1;

        q->rr_count += weighted_rtt;

        debugs(15, 3, "getWeightedRoundRobinParent: weighted_rtt " << weighted_rtt);
    }

    debugs(15, 3, "getWeightedRoundRobinParent: returning " << (q ? q->host : "NULL"));
    return q;
}