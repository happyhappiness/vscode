int
peerHTTPOkay(const CachePeer * p, HttpRequest * request)
{
    if (p->max_conn)
        if (p->stats.conn_open >= p->max_conn)
            return 0;

    if (!peerAllowedToUse(p, request))
        return 0;

    if (!neighborUp(p))
        return 0;

    return 1;
}