void
FwdState::connectStart()
{
    assert(serverDestinations.size() > 0);

    debugs(17, 3, "fwdConnectStart: " << entry->url());

    if (!request->hier.first_conn_start.tv_sec) // first attempt
        request->hier.first_conn_start = current_time;

    /* connection timeout */
    int ctimeout;
    if (serverDestinations[0]->getPeer()) {
        ctimeout = serverDestinations[0]->getPeer()->connect_timeout > 0 ?
                   serverDestinations[0]->getPeer()->connect_timeout : Config.Timeout.peer_connect;
    } else {
        ctimeout = Config.Timeout.connect;
    }

    /* calculate total forwarding timeout ??? */
    int ftimeout = Config.Timeout.forward - (squid_curtime - start_t);
    if (ftimeout < 0)
        ftimeout = 5;

    if (ftimeout < ctimeout)
        ctimeout = ftimeout;

    if (serverDestinations[0]->getPeer() && request->flags.sslBumped) {
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
            serverConn = pinned_connection->validatePinnedConnection(request, serverDestinations[0]->getPeer());
        else
            serverConn = NULL;
        if (Comm::IsConnOpen(serverConn)) {
            pinned_connection->stopPinnedConnectionMonitoring();
            flags.connected_okay = true;
            ++n_tries;
            request->flags.pinned = true;
            request->hier.note(serverConn, pinned_connection->pinning.host);
            if (pinned_connection->pinnedAuth())
                request->flags.auth = true;
            comm_add_close_handler(serverConn->fd, fwdServerClosedWrapper, this);
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
        temp = fwdPconnPool->pop(serverDestinations[0], host, checkRetriable());

    const bool openedPconn = Comm::IsConnOpen(temp);
    pconnRace = openedPconn ? racePossible : raceImpossible;

    // if we found an open persistent connection to use. use it.
    if (openedPconn) {
        serverConn = temp;
        flags.connected_okay = true;
        debugs(17, 3, HERE << "reusing pconn " << serverConnection());
        ++n_tries;

        comm_add_close_handler(serverConnection()->fd, fwdServerClosedWrapper, this);

        /* Update server side TOS and Netfilter mark on the connection. */
        if (Ip::Qos::TheConfig.isAclTosActive()) {
            const tos_t tos = GetTosToServer(request);
            Ip::Qos::setSockTos(temp, tos);
        }
#if SO_MARK
        if (Ip::Qos::TheConfig.isAclNfmarkActive()) {
            const nfmark_t nfmark = GetNfmarkToServer(request);
            Ip::Qos::setSockNfmark(temp, nfmark);
        }
#endif

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

    /* Get the server side TOS and Netfilter mark to be set on the connection. */
    if (Ip::Qos::TheConfig.isAclTosActive()) {
        serverDestinations[0]->tos = GetTosToServer(request);
    }
#if SO_MARK && USE_LIBCAP
    serverDestinations[0]->nfmark = GetNfmarkToServer(request);
    debugs(17, 3, "fwdConnectStart: got outgoing addr " << serverDestinations[0]->local << ", tos " << int(serverDestinations[0]->tos)
           << ", netfilter mark " << serverDestinations[0]->nfmark);
#else
    serverDestinations[0]->nfmark = 0;
    debugs(17, 3, "fwdConnectStart: got outgoing addr " << serverDestinations[0]->local << ", tos " << int(serverDestinations[0]->tos));
#endif

    calls.connector = commCbCall(17,3, "fwdConnectDoneWrapper", CommConnectCbPtrFun(fwdConnectDoneWrapper, this));
    Comm::ConnOpener *cs = new Comm::ConnOpener(serverDestinations[0], calls.connector, ctimeout);
    if (host)
        cs->setHost(host);
    AsyncJob::Start(cs);
}