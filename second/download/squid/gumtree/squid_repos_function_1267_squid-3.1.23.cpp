void
peerSelectInit(void)
{
    memset(&PeerStats, '\0', sizeof(PeerStats));
    assert(sizeof(hier_strings) == (HIER_MAX + 1) * sizeof(char *));
}