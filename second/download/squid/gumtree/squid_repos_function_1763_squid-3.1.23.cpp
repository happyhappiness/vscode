peer *
whichPeer(const IpAddress &from)
{
    int j;

    peer *p = NULL;
    debugs(15, 3, "whichPeer: from " << from);

    for (p = Config.peers; p; p = p->next) {
        for (j = 0; j < p->n_addresses; j++) {
            if (from == p->addresses[j] && from.GetPort() == p->icp.port) {
                return p;
            }
        }
    }

    return NULL;
}