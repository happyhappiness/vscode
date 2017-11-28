static void
comm_select_tcp_incoming(void)
{
    int nfds = 0;
    int fds[MAXTCPLISTENPORTS];
    int nevents;
    tcp_io_events = 0;

    // XXX: only poll sockets that won't be deferred. But how do we identify them?

    for (AnyP::PortCfgPointer s = HttpPortList; s != NULL; s = s->next) {
        if (Comm::IsConnOpen(s->listenConn)) {
            fds[nfds] = s->listenConn->fd;
            ++nfds;
        }
    }

    nevents = comm_check_incoming_select_handlers(nfds, fds);
    incoming_tcp_interval += Config.comm_incoming.tcp.average - nevents;

    if (incoming_tcp_interval < 0)
        incoming_tcp_interval = 0;

    if (incoming_tcp_interval > MAX_INCOMING_INTERVAL)
        incoming_tcp_interval = MAX_INCOMING_INTERVAL;

    if (nevents > INCOMING_TCP_MAX)
        nevents = INCOMING_TCP_MAX;

    statCounter.comm_tcp_incoming.count(nevents);
}