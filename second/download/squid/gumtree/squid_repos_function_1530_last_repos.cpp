void
peerClearRR()
{
    CachePeer *p = NULL;
    for (p = Config.peers; p; p = p->next) {
        p->rr_count = 1;
    }
}