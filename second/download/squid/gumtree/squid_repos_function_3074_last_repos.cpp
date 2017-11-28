static void
clientListenerConnectionOpened(AnyP::PortCfgPointer &s, const Ipc::FdNoteId portTypeNote, const Subscription::Pointer &sub)
{
    Must(s != NULL);

    if (!OpenedHttpSocket(s->listenConn, portTypeNote))
        return;

    Must(Comm::IsConnOpen(s->listenConn));

    // TCP: setup a job to handle accept() with subscribed handler
    AsyncJob::Start(new Comm::TcpAcceptor(s, FdNote(portTypeNote), sub));

    debugs(1, DBG_IMPORTANT, "Accepting " <<
           (s->flags.natIntercept ? "NAT intercepted " : "") <<
           (s->flags.tproxyIntercept ? "TPROXY intercepted " : "") <<
           (s->flags.tunnelSslBumping ? "SSL bumped " : "") <<
           (s->flags.accelSurrogate ? "reverse-proxy " : "")
           << FdNote(portTypeNote) << " connections at "
           << s->listenConn);

    Must(AddOpenedHttpSocket(s->listenConn)); // otherwise, we have received a fd we did not ask for
}