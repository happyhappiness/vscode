void
PeerPoolMgr::openNewConnection()
{
    // KISS: Do nothing else when we are already doing something.
    if (opener != NULL || securer != NULL || shutting_down) {
        debugs(48, 7, "busy: " << opener << '|' << securer << '|' << shutting_down);
        return; // there will be another checkpoint when we are done opening/securing
    }

    // Do not talk to a peer until it is ready.
    if (!neighborUp(peer)) // provides debugging
        return; // there will be another checkpoint when peer is up

    // Do not violate peer limits.
    if (!peerCanOpenMore(peer)) { // provides debugging
        peer->standby.waitingForClose = true; // may already be true
        return; // there will be another checkpoint when a peer conn closes
    }

    // Do not violate global restrictions.
    if (fdUsageHigh()) {
        debugs(48, 7, "overwhelmed");
        peer->standby.waitingForClose = true; // may already be true
        // There will be another checkpoint when a peer conn closes OR when
        // a future pop() fails due to an empty pool. See PconnPool::pop().
        return;
    }

    peer->standby.waitingForClose = false;

    Comm::ConnectionPointer conn = new Comm::Connection;
    Must(peer->n_addresses); // guaranteed by neighborUp() above
    // cycle through all available IP addresses
    conn->remote = peer->addresses[addrUsed++ % peer->n_addresses];
    conn->remote.port(peer->http_port);
    conn->peerType = STANDBY_POOL; // should be reset by peerSelect()
    conn->setPeer(peer);
    getOutgoingAddress(request.getRaw(), conn);
    GetMarkingsToServer(request.getRaw(), *conn);

    const int ctimeout = peerConnectTimeout(peer);
    typedef CommCbMemFunT<PeerPoolMgr, CommConnectCbParams> Dialer;
    opener = JobCallback(48, 5, Dialer, this, PeerPoolMgr::handleOpenedConnection);
    Comm::ConnOpener *cs = new Comm::ConnOpener(conn, opener, ctimeout);
    AsyncJob::Start(cs);
}