static net_db_peer *
netdbPeerByName(const netdbEntry * n, const char *peername)
{
    int i;
    net_db_peer *p = n->peers;

    for (i = 0; i < n->n_peers; ++i, ++p) {
        if (!strcmp(p->peername, peername))
            return p;
    }

    return NULL;
}