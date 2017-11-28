void
PeerPoolMgr::handleOpenedConnection(const CommConnectCbParams &params)
{
    opener = NULL;

    if (!validPeer()) {
        debugs(48, 3, "peer gone");
        if (params.conn != NULL)
            params.conn->close();
        return;
    }

    if (params.flag != Comm::OK) {
        /* it might have been a timeout with a partially open link */
        if (params.conn != NULL)
            params.conn->close();
        peerConnectFailed(peer);
        checkpoint("conn opening failure"); // may retry
        return;
    }

    Must(params.conn != NULL);

    // Handle TLS peers.
    if (peer->secure.encryptTransport) {
        typedef CommCbMemFunT<PeerPoolMgr, CommCloseCbParams> CloserDialer;
        closer = JobCallback(48, 3, CloserDialer, this,
                             PeerPoolMgr::handleSecureClosure);
        comm_add_close_handler(params.conn->fd, closer);

        securer = asyncCall(48, 4, "PeerPoolMgr::handleSecuredPeer",
                            MyAnswerDialer(this, &PeerPoolMgr::handleSecuredPeer));

        const int peerTimeout = peerConnectTimeout(peer);
        const int timeUsed = squid_curtime - params.conn->startTime();
        // Use positive timeout when less than one second is left for conn.
        const int timeLeft = positiveTimeout(peerTimeout - timeUsed);
        auto *connector = new Security::BlindPeerConnector(request, params.conn, securer, nullptr, timeLeft);
        AsyncJob::Start(connector); // will call our callback
        return;
    }

    pushNewConnection(params.conn);
}