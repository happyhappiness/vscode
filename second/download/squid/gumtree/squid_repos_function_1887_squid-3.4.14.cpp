static bool
peerProbeConnect(CachePeer * p)
{
    time_t ctimeout = p->connect_timeout > 0 ? p->connect_timeout : Config.Timeout.peer_connect;
    bool ret = (squid_curtime - p->stats.last_connect_failure) > (ctimeout * 10);

    if (p->testing_now > 0)
        return ret;/* probe already running */

    if (squid_curtime - p->stats.last_connect_probe == 0)
        return ret;/* don't probe to often */

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

    return ret;
}