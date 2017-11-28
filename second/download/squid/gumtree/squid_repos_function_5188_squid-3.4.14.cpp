static void
comm_poll_tcp_incoming(void)
{
    int nfds = 0;
    int fds[MAXTCPLISTENPORTS];
    int j;
    int nevents;
    tcp_io_events = 0;

    // XXX: only poll sockets that won't be deferred. But how do we identify them?

    for (j = 0; j < NHttpSockets; ++j) {
        if (HttpSockets[j] < 0)
            continue;

        fds[nfds] = HttpSockets[j];
        ++nfds;
    }

    nevents = comm_check_incoming_poll_handlers(nfds, fds);
    incoming_tcp_interval = incoming_tcp_interval
                            + Config.comm_incoming.tcp.average - nevents;

    if (incoming_tcp_interval < Config.comm_incoming.tcp.min_poll)
        incoming_tcp_interval = Config.comm_incoming.tcp.min_poll;

    if (incoming_tcp_interval > MAX_INCOMING_INTERVAL)
        incoming_tcp_interval = MAX_INCOMING_INTERVAL;

    if (nevents > INCOMING_TCP_MAX)
        nevents = INCOMING_TCP_MAX;

    statCounter.comm_tcp_incoming.count(nevents);
}