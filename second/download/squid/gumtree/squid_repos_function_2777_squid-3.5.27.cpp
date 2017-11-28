static void
tunnelPeerSelectComplete(Comm::ConnectionList *peer_paths, ErrorState *err, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;

    if (peer_paths == NULL || peer_paths->size() < 1) {
        debugs(26, 3, HERE << "No paths found. Aborting CONNECT");
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

    GetMarkingsToServer(tunnelState->request.getRaw(), *tunnelState->serverDestinations[0]);

    if (tunnelState->request != NULL)
        tunnelState->request->hier.startPeerClock();

    debugs(26, 3, HERE << "paths=" << peer_paths->size() << ", p[0]={" << (*peer_paths)[0] << "}, serverDest[0]={" <<
           tunnelState->serverDestinations[0] << "}");

    AsyncCall::Pointer call = commCbCall(26,3, "tunnelConnectDone", CommConnectCbPtrFun(tunnelConnectDone, tunnelState));
    Comm::ConnOpener *cs = new Comm::ConnOpener(tunnelState->serverDestinations[0], call, Config.Timeout.connect);
    cs->setHost(tunnelState->url);
    AsyncJob::Start(cs);
}