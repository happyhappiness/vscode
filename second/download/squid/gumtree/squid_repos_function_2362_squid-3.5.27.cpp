void
FwdState::connectDone(const Comm::ConnectionPointer &conn, Comm::Flag status, int xerrno)
{
    if (status != Comm::OK) {
        ErrorState *const anErr = makeConnectingError(ERR_CONNECT_FAIL);
        anErr->xerrno = xerrno;
        fail(anErr);

        /* it might have been a timeout with a partially open link */
        if (conn != NULL) {
            if (conn->getPeer())
                peerConnectFailed(conn->getPeer());

            conn->close();
        }
        retryOrBail();
        return;
    }

    serverConn = conn;
    debugs(17, 3, HERE << serverConnection() << ": '" << entry->url() << "'" );

    closeHandler = comm_add_close_handler(serverConnection()->fd, fwdServerClosedWrapper, this);

#if USE_OPENSSL
    if (!request->flags.pinned) {
        const CachePeer *p = serverConnection()->getPeer();
        const bool peerWantsTls = p && p->use_ssl;
        // userWillTlsToPeerForUs assumes CONNECT == HTTPS
        const bool userWillTlsToPeerForUs = p && p->options.originserver &&
                                            request->method == Http::METHOD_CONNECT;
        const bool needTlsToPeer = peerWantsTls && !userWillTlsToPeerForUs;
        const bool needTlsToOrigin = !p && request->url.getScheme() == AnyP::PROTO_HTTPS;
        if (needTlsToPeer || needTlsToOrigin || request->flags.sslPeek) {
            HttpRequest::Pointer requestPointer = request;
            AsyncCall::Pointer callback = asyncCall(17,4,
                                                    "FwdState::ConnectedToPeer",
                                                    FwdStatePeerAnswerDialer(&FwdState::connectedToPeer, this));
            // Use positive timeout when less than one second is left.
            const time_t sslNegotiationTimeout = max(static_cast<time_t>(1), timeLeft());
            Ssl::PeerConnector *connector =
                new Ssl::PeerConnector(requestPointer, serverConnection(), clientConn, callback, sslNegotiationTimeout);
            AsyncJob::Start(connector); // will call our callback
            return;
        }
    }
#endif

    // should reach ConnStateData before the dispatched Client job starts
    CallJobHere1(17, 4, request->clientConnectionManager, ConnStateData,
                 ConnStateData::notePeerConnection, serverConnection());

    dispatch();
}