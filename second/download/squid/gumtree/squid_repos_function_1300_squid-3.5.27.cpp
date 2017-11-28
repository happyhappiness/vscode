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

#if USE_OPENSSL
    // Handle SSL peers.
    if (peer->use_ssl) {
        typedef CommCbMemFunT<PeerPoolMgr, CommCloseCbParams> CloserDialer;
        closer = JobCallback(48, 3, CloserDialer, this,
                             PeerPoolMgr::handleSecureClosure);
        comm_add_close_handler(params.conn->fd, closer);

        securer = asyncCall(48, 4, "PeerPoolMgr::handleSecuredPeer",
                            MyAnswerDialer(this, &PeerPoolMgr::handleSecuredPeer));

        const int peerTimeout = peer->connect_timeout > 0 ?
                                peer->connect_timeout : Config.Timeout.peer_connect;
        const int timeUsed = squid_curtime - params.conn->startTime();
        // Use positive timeout when less than one second is left for conn.
        const int timeLeft = max(1, (peerTimeout - timeUsed));
        Ssl::PeerConnector *connector =
            new Ssl::PeerConnector(request, params.conn, NULL, securer, timeLeft);
        AsyncJob::Start(connector); // will call our callback
        return;
    }
#endif

    pushNewConnection(params.conn);
}