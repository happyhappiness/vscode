CachePeer *
getRoundRobinParent(HttpRequest * request)
{
    CachePeer *p;
    CachePeer *q = NULL;

    for (p = Config.peers; p; p = p->next) {
        if (!p->options.roundrobin)
            continue;

        if (neighborType(p, request) != PEER_PARENT)
            continue;

        if (!peerHTTPOkay(p, request))
            continue;

        if (p->weight == 0)
            continue;

        if (q) {
            if (p->weight == q->weight) {
                if (q->rr_count < p->rr_count)
                    continue;
            } else if ( ((double) q->rr_count / q->weight) < ((double) p->rr_count / p->weight)) {
                continue;
            }
        }

        q = p;
    }

    if (q)
        ++ q->rr_count;

    debugs(15, 3, HERE << "returning " << (q ? q->host : "NULL"));

    return q;
}