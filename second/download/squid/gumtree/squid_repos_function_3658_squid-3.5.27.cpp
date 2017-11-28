static void
httpsAccept(const CommAcceptCbParams &params)
{
    MasterXaction::Pointer xact = params.xaction;
    const AnyP::PortCfgPointer s = xact->squidPort;

    // NP: it is possible the port was reconfigured when the call or accept() was queued.

    if (params.flag != Comm::OK) {
        // Its possible the call was still queued when the client disconnected
        debugs(33, 2, "httpsAccept: " << s->listenConn << ": accept failure: " << xstrerr(params.xerrno));
        return;
    }

    debugs(33, 4, HERE << params.conn << " accepted, starting SSL negotiation.");
    fd_note(params.conn->fd, "client https connect");

    if (s->tcp_keepalive.enabled) {
        commSetTcpKeepalive(params.conn->fd, s->tcp_keepalive.idle, s->tcp_keepalive.interval, s->tcp_keepalive.timeout);
    }

    ++incoming_sockets_accepted;

    // Socket is ready, setup the connection manager to start using it
    ConnStateData *connState = Https::NewServer(xact);
    AsyncJob::Start(connState); // usually async-calls postHttpsAccept()
}