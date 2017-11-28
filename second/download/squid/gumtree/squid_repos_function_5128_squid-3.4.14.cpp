static void
comm_select_udp_incoming(void)
{
    int nfds = 0;
    int fds[2];
    int nevents;
    udp_io_events = 0;

    if (Comm::IsConnOpen(icpIncomingConn)) {
        fds[nfds] = icpIncomingConn->fd;
        ++nfds;
    }

    if (Comm::IsConnOpen(icpOutgoingConn) && icpIncomingConn != icpOutgoingConn) {
        fds[nfds] = icpOutgoingConn->fd;
        ++nfds;
    }

    if (nfds == 0)
        return;

    nevents = comm_check_incoming_select_handlers(nfds, fds);

    incoming_udp_interval += Config.comm_incoming.udp_average - nevents;

    if (incoming_udp_interval < 0)
        incoming_udp_interval = 0;

    if (incoming_udp_interval > MAX_INCOMING_INTERVAL)
        incoming_udp_interval = MAX_INCOMING_INTERVAL;

    if (nevents > INCOMING_UDP_MAX)
        nevents = INCOMING_UDP_MAX;

    statCounter.comm_udp_incoming.count(nevents);
}