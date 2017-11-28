void Adaptation::Icap::Xaction::noteCommConnected(const CommConnectCbParams &io)
{
    cs = NULL;

    if (io.flag == Comm::TIMEOUT) {
        handleCommTimedout();
        return;
    }

    Must(connector != NULL);
    connector = NULL;

    if (io.flag != Comm::OK)
        dieOnConnectionFailure(); // throws

    typedef CommCbMemFunT<Adaptation::Icap::Xaction, CommTimeoutCbParams> TimeoutDialer;
    AsyncCall::Pointer timeoutCall =  asyncCall(93, 5, "Adaptation::Icap::Xaction::noteCommTimedout",
                                      TimeoutDialer(this,&Adaptation::Icap::Xaction::noteCommTimedout));
    commSetConnTimeout(io.conn, TheConfig.connect_timeout(service().cfg().bypass), timeoutCall);

    typedef CommCbMemFunT<Adaptation::Icap::Xaction, CommCloseCbParams> CloseDialer;
    closer =  asyncCall(93, 5, "Adaptation::Icap::Xaction::noteCommClosed",
                        CloseDialer(this,&Adaptation::Icap::Xaction::noteCommClosed));
    comm_add_close_handler(io.conn->fd, closer);

    // If it is a reused connection and the TLS object is built
    // we should not negotiate new TLS session
    const auto &ssl = fd_table[io.conn->fd].ssl;
    if (!ssl && service().cfg().secure.encryptTransport) {
        CbcPointer<Adaptation::Icap::Xaction> me(this);
        securer = asyncCall(93, 4, "Adaptation::Icap::Xaction::handleSecuredPeer",
                            MyIcapAnswerDialer(me, &Adaptation::Icap::Xaction::handleSecuredPeer));

        auto *sslConnector = new Ssl::IcapPeerConnector(theService, io.conn, securer, masterLogEntry(), TheConfig.connect_timeout(service().cfg().bypass));
        AsyncJob::Start(sslConnector); // will call our callback
        return;
    }

// ??    fd_table[io.conn->fd].noteUse(icapPconnPool);
    service().noteConnectionUse(connection);

    handleCommConnected();
}