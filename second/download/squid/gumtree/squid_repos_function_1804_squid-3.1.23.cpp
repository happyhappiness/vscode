static void
peerProbeConnectTimeout(int fd, void *data)
{
    peer * p = (peer *)data;
    comm_remove_close_handler(fd, &peerProbeClosed, p);
    comm_close(fd);
    p->test_fd = -1;
    peerConnectFailedSilent(p);
}