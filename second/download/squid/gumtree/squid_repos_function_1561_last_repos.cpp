static void
peerProbeConnect(CachePeer *p, const bool reprobeIfBusy)
{
    if (peerProbeIsBusy(p)) {
        p->reprobe = reprobeIfBusy;
        return;
    }
    p->reprobe = false;

    const time_t ctimeout = peerConnectTimeout(p);
    /* for each IP address of this CachePeer. find one that we can connect to and probe it. */
    for (int i = 0; i < p->n_addresses; ++i) {
        Comm::ConnectionPointer conn = new Comm::Connection;
        conn->remote = p->addresses[i];
        conn->remote.port(p->http_port);
        conn->setPeer(p);
        getOutgoingAddress(NULL, conn);

        ++ p->testing_now;

        AsyncCall::Pointer call = commCbCall(15,3, "peerProbeConnectDone", CommConnectCbPtrFun(peerProbeConnectDone, p));
        Comm::ConnOpener *cs = new Comm::ConnOpener(conn, call, ctimeout);
        cs->setHost(p->host);
        AsyncJob::Start(cs);
    }

    p->stats.last_connect_probe = squid_curtime;
}