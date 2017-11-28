CachePeer *
whichPeer(const Ip::Address &from)
{
    int j;

    CachePeer *p = NULL;
    debugs(15, 3, "whichPeer: from " << from);

    for (p = Config.peers; p; p = p->next) {
        for (j = 0; j < p->n_addresses; ++j) {
            if (from == p->addresses[j] && from.port() == p->icp.port) {
                return p;
            }
        }
    }

    return NULL;
}