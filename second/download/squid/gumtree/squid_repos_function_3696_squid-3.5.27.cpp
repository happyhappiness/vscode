void
ConnStateData::pinConnection(const Comm::ConnectionPointer &pinServer, const HttpRequest::Pointer &request)
{
    if (Comm::IsConnOpen(pinning.serverConnection) &&
            pinning.serverConnection->fd == pinServer->fd) {
        debugs(33, 3, "already pinned" << pinServer);
        return;
    }

    unpinConnection(true); // closes pinned connection, if any, and resets fields

    pinning.serverConnection = pinServer;

    debugs(33, 3, HERE << pinning.serverConnection);

    Must(pinning.serverConnection != NULL);

    const char *pinnedHost = "[unknown]";
    if (request != NULL) {
        pinning.host = xstrdup(request->GetHost());
        pinning.port = request->port;
        pinnedHost = pinning.host;
        pinning.auth = request->flags.connectionAuth;
    } else {
        pinning.port = pinServer->remote.port();
    }
    pinning.pinned = true;
    pinning.peer = cbdataReference(pinServer->getPeer());
    char stmp[MAX_IPSTRLEN];
    char desc[FD_DESC_SZ];
    snprintf(desc, FD_DESC_SZ, "%s pinned connection for %s (%d)",
             (pinning.auth || !pinning.peer) ? pinnedHost : pinning.peer->name,
             clientConnection->remote.toUrl(stmp,MAX_IPSTRLEN),
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
}