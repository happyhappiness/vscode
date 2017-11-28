void
Adaptation::Icap::Xaction::dnsLookupDone(const ipcache_addrs *ia)
{
    Adaptation::Icap::ServiceRep &s = service();

    if (ia == NULL) {
        debugs(44, DBG_IMPORTANT, "ICAP: Unknown service host: " << s.cfg().host);

#if WHEN_IPCACHE_NBGETHOSTBYNAME_USES_ASYNC_CALLS
        dieOnConnectionFailure(); // throws
#else // take a step back into protected Async call dialing.
        // fake the connect callback
        typedef CommCbMemFunT<Adaptation::Icap::Xaction, CommConnectCbParams> Dialer;
        CbcPointer<Xaction> self(this);
        Dialer dialer(self, &Adaptation::Icap::Xaction::noteCommConnected);
        dialer.params.conn = connection;
        dialer.params.flag = COMM_ERROR;
        // fake other parameters by copying from the existing connection
        connector = asyncCall(93,3, "Adaptation::Icap::Xaction::noteCommConnected", dialer);
        ScheduleCallHere(connector);
#endif
        return;
    }

    assert(ia->cur < ia->count);

    connection = new Comm::Connection;
    connection->remote = ia->in_addrs[ia->cur];
    connection->remote.SetPort(s.cfg().port);
    getOutgoingAddress(NULL, connection);

    // TODO: service bypass status may differ from that of a transaction
    typedef CommCbMemFunT<Adaptation::Icap::Xaction, CommConnectCbParams> ConnectDialer;
    connector = JobCallback(93,3, ConnectDialer, this, Adaptation::Icap::Xaction::noteCommConnected);
    cs = new Comm::ConnOpener(connection, connector, TheConfig.connect_timeout(service().cfg().bypass));
    cs->setHost(s.cfg().host.termedBuf());
    AsyncJob::Start(cs);
}