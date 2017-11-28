CachePeer *
netdbClosestParent(HttpRequest * request)
{
#if USE_ICMP
    CachePeer *p = NULL;
    netdbEntry *n;
    const ipcache_addrs *ia;
    net_db_peer *h;
    int i;
    n = netdbLookupHost(request->GetHost());

    if (NULL == n) {
        /* try IP addr */
        ia = ipcache_gethostbyname(request->GetHost(), 0);

        if (NULL != ia)
            n = netdbLookupAddr(ia->in_addrs[ia->cur]);
    }

    if (NULL == n)
        return NULL;

    if (0 == n->n_peers)
        return NULL;

    n->last_use_time = squid_curtime;

    /*
     * Find the parent with the least RTT to the origin server.
     * Make sure we don't return a parent who is farther away than
     * we are.  Note, the n->peers list is pre-sorted by RTT.
     */
    for (i = 0; i < n->n_peers; ++i) {
        h = &n->peers[i];

        if (n->rtt > 0)
            if (n->rtt < h->rtt)
                break;

        p = peerFindByName(h->peername);

        if (NULL == p)      /* not found */
            continue;

        if (neighborType(p, request) != PEER_PARENT)
            continue;

        if (!peerHTTPOkay(p, request))  /* not allowed */
            continue;

        return p;
    }

#endif
    return NULL;
}