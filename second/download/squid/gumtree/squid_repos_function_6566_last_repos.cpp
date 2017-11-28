static void
netdbRelease(netdbEntry * n)
{
    net_db_name *x;
    net_db_name *next;

    for (x = n->hosts; x; x = next) {
        next = x->next;
        netdbHostDelete(x);
    }

    n->hosts = NULL;
    safe_free(n->peers);
    n->peers = NULL;
    n->n_peers = 0;
    n->n_peers_alloc = 0;

    if (n->link_count == 0) {
        netdbHashDelete(n->network);
        delete n;
    }
}