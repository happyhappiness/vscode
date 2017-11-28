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

    if (!request->flags.pinned) {
        const CachePeer *p = serverConnection()->getPeer();
        const bool peerWantsTls = p && p->secure.encryptTransport;
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
            const time_t connTimeout = serverDestinations[0]->connectTimeout(start_t);
            const time_t sslNegotiationTimeout = positiveTimeout(connTimeout);
            Security::PeerConnector *connector = nullptr;
#if USE_OPENSSL
            if (request->flags.sslPeek)
                connector = new Ssl::PeekingPeerConnector(requestPointer, serverConnection(), clientConn, callback, al, sslNegotiationTimeout);
            else
#endif
                connector = new Security::BlindPeerConnector(requestPointer, serverConnection(), callback, al, sslNegotiationTimeout);
            AsyncJob::Start(connector); // will call our callback
            return;
        }
    }

    // if not encrypting just run the post-connect actions
    Security::EncryptorAnswer nil;
    connectedToPeer(nil);
}