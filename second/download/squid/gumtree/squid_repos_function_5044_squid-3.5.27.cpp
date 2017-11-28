bool
Ftp::Server::checkDataConnPre()
{
    if (Comm::IsConnOpen(dataConn))
        return true;

    if (Comm::IsConnOpen(dataListenConn)) {
        // We are still waiting for a client to connect to us after PASV.
        // Perhaps client's data conn handshake has not reached us yet.
        // After we talk to the server, checkDataConnPost() will recheck.
        debugs(33, 3, "expecting clt data conn " << dataListenConn);
        return true;
    }

    if (!dataConn || dataConn->remote.isAnyAddr()) {
        debugs(33, 5, "missing " << dataConn);
        // TODO: use client address and default port instead.
        setReply(425, "Use PORT or PASV first");
        return false;
    }

    // active transfer: open a data connection from Squid to client
    typedef CommCbMemFunT<Server, CommConnectCbParams> Dialer;
    connector = JobCallback(17, 3, Dialer, this, Ftp::Server::connectedForData);
    Comm::ConnOpener *cs = new Comm::ConnOpener(dataConn, connector,
            Config.Timeout.connect);
    AsyncJob::Start(cs);
    return false; // ConnStateData::processFtpRequest waits handleConnectDone
}