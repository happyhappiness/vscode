void Adaptation::Icap::Xaction::openConnection()
{
    IpAddress client_addr;

    Must(connection < 0);

    const Adaptation::Service &s = service();

    if (!TheConfig.reuse_connections)
        disableRetries(); // this will also safely drain pconn pool

    // TODO: check whether NULL domain is appropriate here
    connection = icapPconnPool->pop(s.cfg().host.termedBuf(), s.cfg().port, NULL, client_addr, isRetriable);
    if (connection >= 0) {
        debugs(93,3, HERE << "reused pconn FD " << connection);

        // fake the connect callback
        // TODO: can we sync call Adaptation::Icap::Xaction::noteCommConnected here instead?
        typedef CommCbMemFunT<Adaptation::Icap::Xaction, CommConnectCbParams> Dialer;
        CbcPointer<Xaction> self(this);
        Dialer dialer(self, &Adaptation::Icap::Xaction::noteCommConnected);
        dialer.params.fd = connection;
        dialer.params.flag = COMM_OK;
        // fake other parameters by copying from the existing connection
        connector = asyncCall(93,3, "Adaptation::Icap::Xaction::noteCommConnected", dialer);
        ScheduleCallHere(connector);
        return;
    }

    disableRetries(); // we only retry pconn failures

    IpAddress outgoing;
    if (!Ip::EnableIpv6 && !outgoing.SetIPv4()) {
        debugs(31, DBG_CRITICAL, "ERROR: IPv6 is disabled. " << outgoing << " is not an IPv4 address.");
        dieOnConnectionFailure(); // throws
    }
    /* split-stack for now requires default IPv4-only socket */
    if (Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK && outgoing.IsAnyAddr() && !s.cfg().ipv6) {
        outgoing.SetIPv4();
    }

    connection = comm_open(SOCK_STREAM, 0, outgoing,
                           COMM_NONBLOCKING, s.cfg().uri.termedBuf());

    if (connection < 0)
        dieOnConnectionFailure(); // throws

    debugs(93,3, typeName << " opens connection to " << s.cfg().host << ":" << s.cfg().port);

    // TODO: service bypass status may differ from that of a transaction
    typedef CommCbMemFunT<Adaptation::Icap::Xaction, CommTimeoutCbParams> TimeoutDialer;
    AsyncCall::Pointer timeoutCall = JobCallback(93, 5,
                                     TimeoutDialer, this, Adaptation::Icap::Xaction::noteCommTimedout);
    commSetTimeout(connection, TheConfig.connect_timeout(
                       service().cfg().bypass), timeoutCall);

    typedef CommCbMemFunT<Adaptation::Icap::Xaction, CommCloseCbParams> CloseDialer;
    closer = JobCallback(93, 5,
                         CloseDialer, this, Adaptation::Icap::Xaction::noteCommClosed);
    comm_add_close_handler(connection, closer);

    typedef CommCbMemFunT<Adaptation::Icap::Xaction, CommConnectCbParams> ConnectDialer;
    connector = JobCallback(93,3,
                            ConnectDialer, this, Adaptation::Icap::Xaction::noteCommConnected);
    commConnectStart(connection, s.cfg().host.termedBuf(), s.cfg().port, connector);
}