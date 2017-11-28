static net_db_peer *
netdbPeerAdd(netdbEntry * n, CachePeer * e)
{
    net_db_peer *p;
    net_db_peer *o;
    int osize;
    int i;

    if (n->n_peers == n->n_peers_alloc) {
        o = n->peers;
        osize = n->n_peers_alloc;

        if (n->n_peers_alloc == 0)
            n->n_peers_alloc = 2;
        else
            n->n_peers_alloc <<= 1;

        debugs(38, 3, "netdbPeerAdd: Growing peer list for '" << n->network << "' to " << n->n_peers_alloc);

        n->peers = (net_db_peer *)xcalloc(n->n_peers_alloc, sizeof(net_db_peer));

        for (i = 0; i < osize; ++i)
            *(n->peers + i) = *(o + i);

        if (osize) {
            safe_free(o);
        }
    }

    p = n->peers + n->n_peers;
    p->peername = netdbPeerName(e->host);
    ++ n->n_peers;
    return p;
}