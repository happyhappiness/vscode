static void
peerProbeConnectDone(int fd, const DnsLookupDetails &, comm_err_t status, int xerrno, void *data)
{
    peer *p = (peer*)data;

    if (status == COMM_OK) {
        peerConnectSucceded(p);
    } else {
        peerConnectFailedSilent(p);
    }

    comm_remove_close_handler(fd, &peerProbeClosed, p);
    comm_close(fd);
    p->test_fd = -1;
    return;
}