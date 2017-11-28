static void
clientListenerConnectionOpened(AnyP::PortCfg *s, const Ipc::FdNoteId portTypeNote, const Subscription::Pointer &sub)
{
    if (!OpenedHttpSocket(s->listenConn, portTypeNote))
        return;

    Must(s);
    Must(Comm::IsConnOpen(s->listenConn));

    // TCP: setup a job to handle accept() with subscribed handler
    AsyncJob::Start(new Comm::TcpAcceptor(s->listenConn, FdNote(portTypeNote), sub));

    debugs(1, DBG_IMPORTANT, "Accepting " <<
           (s->intercepted ? "NAT intercepted " : "") <<
           (s->spoof_client_ip ? "TPROXY spoofing " : "") <<
           (s->sslBump ? "SSL bumped " : "") <<
           (s->accel ? "reverse-proxy " : "")
           << FdNote(portTypeNote) << " connections at "
           << s->listenConn);

    Must(AddOpenedHttpSocket(s->listenConn)); // otherwise, we have received a fd we did not ask for
}