void Adaptation::Icap::Xaction::noteCommConnected(const CommConnectCbParams &io)
{
    cs = NULL;

    if (io.flag == COMM_TIMEOUT) {
        handleCommTimedout();
        return;
    }

    Must(connector != NULL);
    connector = NULL;

    if (io.flag != COMM_OK)
        dieOnConnectionFailure(); // throws

    typedef CommCbMemFunT<Adaptation::Icap::Xaction, CommTimeoutCbParams> TimeoutDialer;
    AsyncCall::Pointer timeoutCall =  asyncCall(93, 5, "Adaptation::Icap::Xaction::noteCommTimedout",
                                      TimeoutDialer(this,&Adaptation::Icap::Xaction::noteCommTimedout));
    commSetConnTimeout(io.conn, TheConfig.connect_timeout(service().cfg().bypass), timeoutCall);

    typedef CommCbMemFunT<Adaptation::Icap::Xaction, CommCloseCbParams> CloseDialer;
    closer =  asyncCall(93, 5, "Adaptation::Icap::Xaction::noteCommClosed",
                        CloseDialer(this,&Adaptation::Icap::Xaction::noteCommClosed));
    comm_add_close_handler(io.conn->fd, closer);

// ??    fd_table[io.conn->fd].noteUse(icapPconnPool);
    service().noteConnectionUse(connection);

    handleCommConnected();
}