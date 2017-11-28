static void
free_peer(CachePeer ** P)
{
    delete *P;
    *P = NULL;
    Config.npeers = 0;
}