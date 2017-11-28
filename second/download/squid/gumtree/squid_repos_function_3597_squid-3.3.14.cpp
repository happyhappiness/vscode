void
ConnStateData::pinConnection(const Comm::ConnectionPointer &pinServer, HttpRequest *request, CachePeer *aPeer, bool auth)
{
    char desc[FD_DESC_SZ];

    if (Comm::IsConnOpen(pinning.serverConnection)) {
        if (pinning.serverConnection->fd == pinServer->fd) {
            startPinnedConnectionMonitoring();
            return;
        }
    }

    unpinConnection(); // closes pinned connection, if any, and resets fields

    pinning.serverConnection = pinServer;

    debugs(33, 3, HERE << pinning.serverConnection);

    // when pinning an SSL bumped connection, the request may be NULL
    const char *pinnedHost = "[unknown]";
    if (request) {
        pinning.host = xstrdup(request->GetHost());
        pinning.port = request->port;
        pinnedHost = pinning.host;
    } else {
        pinning.port = pinServer->remote.GetPort();
    }
    pinning.pinned = true;
    if (aPeer)
        pinning.peer = cbdataReference(aPeer);
    pinning.auth = auth;
    char stmp[MAX_IPSTRLEN];
    snprintf(desc, FD_DESC_SZ, "%s pinned connection for %s (%d)",
             (auth || !aPeer) ? pinnedHost : aPeer->name,
             clientConnection->remote.ToURL(stmp,MAX_IPSTRLEN),
             clientConnection->fd);
    fd_note(pinning.serverConnection->fd, desc);

    typedef CommCbMemFunT<ConnStateData, CommCloseCbParams> Dialer;
    pinning.closeHandler = JobCallback(33, 5,
                                       Dialer, this, ConnStateData::clientPinnedConnectionClosed);
    // remember the pinned connection so that cb does not unpin a fresher one
    typedef CommCloseCbParams Params;
    Params &params = GetCommParams<Params>(pinning.closeHandler);
    params.conn = pinning.serverConnection;
    comm_add_close_handler(pinning.serverConnection->fd, pinning.closeHandler);

    startPinnedConnectionMonitoring();
}