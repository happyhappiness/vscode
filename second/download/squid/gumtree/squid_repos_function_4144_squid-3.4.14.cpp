void
Adaptation::Icap::Xaction::openConnection()
{
    Must(!haveConnection());

    Adaptation::Icap::ServiceRep &s = service();

    if (!TheConfig.reuse_connections)
        disableRetries(); // this will also safely drain pconn pool

    bool wasReused = false;
    connection = s.getConnection(isRetriable, wasReused);

    if (wasReused && Comm::IsConnOpen(connection)) {
        // Set comm Close handler
        // fake the connect callback
        // TODO: can we sync call Adaptation::Icap::Xaction::noteCommConnected here instead?
        typedef CommCbMemFunT<Adaptation::Icap::Xaction, CommConnectCbParams> Dialer;
        CbcPointer<Xaction> self(this);
        Dialer dialer(self, &Adaptation::Icap::Xaction::noteCommConnected);
        dialer.params.conn = connection;
        dialer.params.flag = COMM_OK;
        // fake other parameters by copying from the existing connection
        connector = asyncCall(93,3, "Adaptation::Icap::Xaction::noteCommConnected", dialer);
        ScheduleCallHere(connector);
        return;
    }

    disableRetries(); // we only retry pconn failures

    // Attempt to open a new connection...
    debugs(93,3, typeName << " opens connection to " << s.cfg().host.termedBuf() << ":" << s.cfg().port);

    // Locate the Service IP(s) to open
    ipcache_nbgethostbyname(s.cfg().host.termedBuf(), icapLookupDnsResults, this);
}