void
Ftp::Client::connectDataChannel()
{
    if (!Comm::IsConnOpen(ctrl.conn)) {
        debugs(9, 5, "The control connection to the remote end is closed");
        return;
    }

    safe_free(ctrl.last_command);

    safe_free(ctrl.last_reply);

    ctrl.last_command = xstrdup("Connect to server data port");

    // Generate a new data channel descriptor to be opened.
    Comm::ConnectionPointer conn = new Comm::Connection;
    conn->setAddrs(ctrl.conn->local, data.host);
    conn->local.port(0);
    conn->remote.port(data.port);
    conn->tos = ctrl.conn->tos;
    conn->nfmark = ctrl.conn->nfmark;

    debugs(9, 3, "connecting to " << conn->remote);

    typedef CommCbMemFunT<Client, CommConnectCbParams> Dialer;
    data.opener = JobCallback(9, 3, Dialer, this, Ftp::Client::dataChannelConnected);
    Comm::ConnOpener *cs = new Comm::ConnOpener(conn, data.opener, Config.Timeout.connect);
    cs->setHost(data.host);
    AsyncJob::Start(cs);
}