static void
comm_poll_icp_incoming(void)
{
    int nfds = 0;
    int fds[2];
    int nevents;
    icp_io_events = 0;

    if (theInIcpConnection >= 0)
        fds[nfds++] = theInIcpConnection;

    if (theInIcpConnection != theOutIcpConnection)
        if (theOutIcpConnection >= 0)
            fds[nfds++] = theOutIcpConnection;

    if (nfds == 0)
        return;

    nevents = comm_check_incoming_poll_handlers(nfds, fds);

    incoming_icp_interval += Config.comm_incoming.icp_average - nevents;

    if (incoming_icp_interval < Config.comm_incoming.icp_min_poll)
        incoming_icp_interval = Config.comm_incoming.icp_min_poll;

    if (incoming_icp_interval > MAX_INCOMING_INTERVAL)
        incoming_icp_interval = MAX_INCOMING_INTERVAL;

    if (nevents > INCOMING_ICP_MAX)
        nevents = INCOMING_ICP_MAX;

    statHistCount(&statCounter.comm_icp_incoming, nevents);
}