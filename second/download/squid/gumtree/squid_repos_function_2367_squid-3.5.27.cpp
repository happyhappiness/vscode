void
FwdState::connectStart()
{
    assert(serverDestinations.size() > 0);

    debugs(17, 3, "fwdConnectStart: " << entry->url());

    request->hier.startPeerClock();

    // Do not fowrward bumped connections to parent proxy unless it is an
    // origin server
    if (serverDestinations[0]->getPeer() && !serverDestinations[0]->getPeer()->options.originserver && request->flags.sslBumped) {
        debugs(50, 4, "fwdConnectStart: Ssl bumped connections through parent proxy are not allowed");
        ErrorState *anErr = new ErrorState(ERR_CANNOT_FORWARD, Http::scServiceUnavailable, request);
        fail(anErr);
        self = NULL; // refcounted
        return;
    }

    request->flags.pinned = false; // XXX: what if the ConnStateData set this to flag existing credentials?
    // XXX: answer: the peer selection *should* catch it and give us only the pinned peer. so we reverse the =0 step below.
    // XXX: also, logs will now lie if pinning is broken and leads to an error message.
    if (serverDestinations[0]->peerType == PINNED) {
        ConnStateData *pinned_connection = request->pinnedConnection();
        debugs(17,7, "pinned peer connection: " << pinned_connection);
        // pinned_connection may become nil after a pconn race
        if (pinned_connection)
            serverConn = pinned_connection->borrowPinnedConnection(request, serverDestinations[0]->getPeer());
        else
            serverConn = NULL;
        if (Comm::IsConnOpen(serverConn)) {
            pinned_connection->stopPinnedConnectionMonitoring();
            flags.connected_okay = true;
            ++n_tries;
            request->flags.pinned = true;
            if (pinned_connection->pinnedAuth())
                request->flags.auth = true;

            closeHandler = comm_add_close_handler(serverConn->fd,  fwdServerClosedWrapper, this);

            syncWithServerConn(pinned_connection->pinning.host);

            // the server may close the pinned connection before this request
            pconnRace = racePossible;
            dispatch();
            return;
        }
        // Pinned connection failure.
        debugs(17,2,HERE << "Pinned connection failed: " << pinned_connection);
        ErrorState *anErr = new ErrorState(ERR_ZERO_SIZE_OBJECT, Http::scServiceUnavailable, request);
        fail(anErr);
        self = NULL; // refcounted
        return;
    }

    // Use pconn to avoid opening a new connection.
    const char *host = NULL;
    if (!serverDestinations[0]->getPeer())
        host = request->GetHost();

    Comm::ConnectionPointer temp;
    // Avoid pconns after races so that the same client does not suffer twice.
    // This does not increase the total number of connections because we just
    // closed the connection that failed the race. And re-pinning assumes this.
    if (pconnRace != raceHappened)
        temp = pconnPop(serverDestinations[0], host);

    const bool openedPconn = Comm::IsConnOpen(temp);
    pconnRace = openedPconn ? racePossible : raceImpossible;

    // if we found an open persistent connection to use. use it.
    if (openedPconn) {
        serverConn = temp;
        flags.connected_okay = true;
        debugs(17, 3, HERE << "reusing pconn " << serverConnection());
        ++n_tries;

        closeHandler = comm_add_close_handler(serverConnection()->fd,  fwdServerClosedWrapper, this);

        syncWithServerConn(request->GetHost());

        dispatch();
        return;
    }

    // We will try to open a new connection, possibly to the same destination.
    // We reset serverDestinations[0] in case we are using it again because
    // ConnOpener modifies its destination argument.
    serverDestinations[0]->local.port(0);
    serverConn = NULL;

#if URL_CHECKSUM_DEBUG
    entry->mem_obj->checkUrlChecksum();
#endif

    GetMarkingsToServer(request, *serverDestinations[0]);

    calls.connector = commCbCall(17,3, "fwdConnectDoneWrapper", CommConnectCbPtrFun(fwdConnectDoneWrapper, this));
    Comm::ConnOpener *cs = new Comm::ConnOpener(serverDestinations[0], calls.connector, timeLeft());
    if (host)
        cs->setHost(host);
    AsyncJob::Start(cs);
}