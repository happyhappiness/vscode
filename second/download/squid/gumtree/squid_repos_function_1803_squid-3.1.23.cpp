static void
peerProbeClosed(int fd, void *data)
{
    peer *p = (peer*)data;
    p->test_fd = -1;
    // it is a failure because we failed to connect
    peerConnectFailedSilent(p);
}