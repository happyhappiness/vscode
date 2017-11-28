static void
tunnelPeerSelectComplete(Comm::ConnectionList *peer_paths, ErrorState *err, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;

    bool bail = false;
    if (!peer_paths || peer_paths->empty()) {
        debugs(26, 3, HERE << "No paths found. Aborting CONNECT");
        bail = true;
    }

    if (!bail && tunnelState->serverDestinations[0]->peerType == PINNED) {
        Comm::ConnectionPointer serverConn = borrowPinnedConnection(tunnelState->request.getRaw(), tunnelState->serverDestinations[0]);
        debugs(26,7, "pinned peer connection: " << serverConn);
        if (Comm::IsConnOpen(serverConn)) {
            tunnelConnectDone(serverConn, Comm::OK, 0, (void *)tunnelState);
            return;
        }
        bail = true;
    }

    if (bail) {
        if (!err) {
            err = new ErrorState(ERR_CANNOT_FORWARD, Http::scServiceUnavailable, tunnelState->request.getRaw());
        }
        *tunnelState->status_ptr = err->httpStatus;
        err->callback = tunnelErrorComplete;
        err->callback_data = tunnelState;
        errorSend(tunnelState->client.conn, err);
        return;
    }
    delete err;

    if (tunnelState->request != NULL)
        tunnelState->request->hier.startPeerClock();

    debugs(26, 3, "paths=" << peer_paths->size() << ", p[0]={" << (*peer_paths)[0] << "}, serverDest[0]={" <<
           tunnelState->serverDestinations[0] << "}");

    tunnelState->startConnecting();
}