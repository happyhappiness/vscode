
        if (peer->sslSession)
            SSL_set_session(ssl, peer->sslSession);

    } else {
        SSL_set_ex_data(ssl, ssl_ex_index_server, (void*)request->GetHost());

        // We need to set SNI TLS extension only in the case we are
        // connecting direct to origin server
        Ssl::setClientSNI(ssl, request->GetHost());
    }

    // Create the ACL check list now, while we have access to more info.
    // The list is used in ssl_verify_cb() and is freed in ssl_free().
    if (acl_access *acl = Config.ssl_client.cert_error) {
        ACLFilledChecklist *check = new ACLFilledChecklist(acl, request, dash_str);
        SSL_set_ex_data(ssl, ssl_ex_index_cert_error_check, check);
    }

    fd_table[fd].ssl = ssl;
    fd_table[fd].read_method = &ssl_read_method;
    fd_table[fd].write_method = &ssl_write_method;
    negotiateSSL(fd);
}

#endif

void
FwdState::connectDone(const Comm::ConnectionPointer &conn, comm_err_t status, int xerrno)
{
    if (status != COMM_OK) {
        ErrorState *const anErr = makeConnectingError(ERR_CONNECT_FAIL);
        anErr->xerrno = xerrno;
        fail(anErr);

        /* it might have been a timeout with a partially open link */
        if (conn != NULL) {
            if (conn->getPeer())
                peerConnectFailed(conn->getPeer());

            conn->close();
        }
        retryOrBail();
        return;
    }

    serverConn = conn;
    flags.connected_okay = true;

    debugs(17, 3, HERE << serverConnection() << ": '" << entry->url() << "'" );

    comm_add_close_handler(serverConnection()->fd, fwdServerClosedWrapper, this);

    if (serverConnection()->getPeer())
        peerConnectSucceded(serverConnection()->getPeer());

#if USE_SSL
    if (!request->flags.pinned) {
        if ((serverConnection()->getPeer() && serverConnection()->getPeer()->use_ssl) ||
                (!serverConnection()->getPeer() && request->protocol == AnyP::PROTO_HTTPS)) {
            initiateSSL();
            return;
        }
    }
#endif

    dispatch();
}

void
FwdState::connectTimeout(int fd)
{
    debugs(17, 2, "fwdConnectTimeout: FD " << fd << ": '" << entry->url() << "'" );
    assert(serverDestinations[0] != NULL);
    assert(fd == serverDestinations[0]->fd);

    if (entry->isEmpty()) {
        ErrorState *anErr = new ErrorState(ERR_CONNECT_FAIL, HTTP_GATEWAY_TIMEOUT, request);
        anErr->xerrno = ETIMEDOUT;
        fail(anErr);

        /* This marks the peer DOWN ... */
        if (serverDestinations[0]->getPeer())
            peerConnectFailed(serverDestinations[0]->getPeer());
    }

    if (Comm::IsConnOpen(serverDestinations[0])) {
        serverDestinations[0]->close();
    }
}

/**
 * Called after Forwarding path selection (via peer select) has taken place.
 * And whenever forwarding needs to attempt a new connection (routing failover)
 * We have a vector of possible localIP->remoteIP paths now ready to start being connected.
 */
void
FwdState::connectStart()
{
    assert(serverDestinations.size() > 0);

    debugs(17, 3, "fwdConnectStart: " << entry->url());

    if (n_tries == 0) // first attempt
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

    if (serverDestinations[0]->getPeer() && request->flags.sslBumped == true) {
        debugs(50, 4, "fwdConnectStart: Ssl bumped connections through parrent proxy are not allowed");
        ErrorState *anErr = new ErrorState(ERR_CANNOT_FORWARD, HTTP_SERVICE_UNAVAILABLE, request);
        fail(anErr);
        self = NULL; // refcounted
        return;
    }

    request->flags.pinned = 0; // XXX: what if the ConnStateData set this to flag existing credentials?
    // XXX: answer: the peer selection *should* catch it and give us only the pinned peer. so we reverse the =0 step below.
    // XXX: also, logs will now lie if pinning is broken and leads to an error message.
    if (serverDestinations[0]->peerType == PINNED) {
        ConnStateData *pinned_connection = request->pinnedConnection();
        // pinned_connection may become nil after a pconn race
        if (pinned_connection)
            serverConn = pinned_connection->validatePinnedConnection(request, serverDestinations[0]->getPeer());
        else
            serverConn = NULL;
        if (Comm::IsConnOpen(serverConn)) {
            flags.connected_okay = true;
#if 0
            if (!serverConn->getPeer())
                serverConn->peerType = HIER_DIRECT;
#endif
            ++n_tries;
            request->flags.pinned = 1;
            if (pinned_connection->pinnedAuth())
                request->flags.auth = 1;
            // the server may close the pinned connection before this request
            pconnRace = racePossible;
            dispatch();
            return;
        }
        /* Failure. Fall back on next path */
        debugs(17,2,HERE << " Pinned connection " << pinned_connection << " not valid.");
        serverDestinations.shift();
        startConnectionOrFail();
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
            temp->tos = GetTosToServer(request);
            Ip::Qos::setSockTos(temp, temp->tos);
        }
#if SO_MARK
        if (Ip::Qos::TheConfig.isAclNfmarkActive()) {
            temp->nfmark = GetNfmarkToServer(request);
            Ip::Qos::setSockNfmark(temp, temp->nfmark);
        }
#endif

        dispatch();
        return;
    }

    // We will try to open a new connection, possibly to the same destination.
    // We reset serverDestinations[0] in case we are using it again because
    // ConnOpener modifies its destination argument.
    serverDestinations[0]->local.SetPort(0);
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

void
FwdState::dispatch()
{
    debugs(17, 3, HERE << clientConn << ": Fetching '" << RequestMethodStr(request->method) << " " << entry->url() << "'");
    /*
     * Assert that server_fd is set.  This is to guarantee that fwdState
     * is attached to something and will be deallocated when server_fd
     * is closed.
     */
    assert(Comm::IsConnOpen(serverConn));

    fd_note(serverConnection()->fd, entry->url());

    fd_table[serverConnection()->fd].noteUse(fwdPconnPool);

    /*assert(!EBIT_TEST(entry->flags, ENTRY_DISPATCHED)); */
    assert(entry->ping_status != PING_WAITING);

    assert(entry->lock_count);

    EBIT_SET(entry->flags, ENTRY_DISPATCHED);

    netdbPingSite(request->GetHost());

    /* Retrieves remote server TOS or MARK value, and stores it as part of the
     * original client request FD object. It is later used to forward
     * remote server's TOS/MARK in the response to the client in case of a MISS.
     */
    if (Ip::Qos::TheConfig.isHitNfmarkActive()) {
        if (Comm::IsConnOpen(clientConn) && Comm::IsConnOpen(serverConnection())) {
            fde * clientFde = &fd_table[clientConn->fd]; // XXX: move the fd_table access into Ip::Qos
            /* Get the netfilter mark for the connection */
            Ip::Qos::getNfmarkFromServer(serverConnection(), clientFde);
        }
    }

#if _SQUID_LINUX_
    /* Bug 2537: The TOS forward part of QOS only applies to patched Linux kernels. */
    if (Ip::Qos::TheConfig.isHitTosActive()) {
        if (Comm::IsConnOpen(clientConn)) {
            fde * clientFde = &fd_table[clientConn->fd]; // XXX: move the fd_table access into Ip::Qos
            /* Get the TOS value for the packet */
            Ip::Qos::getTosFromServer(serverConnection(), clientFde);
        }
    }
#endif

    if (serverConnection()->getPeer() != NULL) {
        ++ serverConnection()->getPeer()->stats.fetches;
        request->peer_login = serverConnection()->getPeer()->login;
        request->peer_domain = serverConnection()->getPeer()->domain;
        httpStart(this);
    } else {
        request->peer_login = NULL;
        request->peer_domain = NULL;

        switch (request->protocol) {
#if USE_SSL

        case AnyP::PROTO_HTTPS:
            httpStart(this);
            break;
#endif

        case AnyP::PROTO_HTTP:
            httpStart(this);
            break;

        case AnyP::PROTO_GOPHER:
            gopherStart(this);
            break;

        case AnyP::PROTO_FTP:
            ftpStart(this);
            break;

        case AnyP::PROTO_CACHE_OBJECT:

        case AnyP::PROTO_INTERNAL:

        case AnyP::PROTO_URN:
            fatal_dump("Should never get here");
            break;

        case AnyP::PROTO_WHOIS:
            whoisStart(this);
            break;

        case AnyP::PROTO_WAIS:	/* Not implemented */

        default:
            debugs(17, DBG_IMPORTANT, "WARNING: Cannot retrieve '" << entry->url() << "'.");
            ErrorState *anErr = new ErrorState(ERR_UNSUP_REQ, HTTP_BAD_REQUEST, request);
            fail(anErr);
            // Set the dont_retry flag because this is not a transient (network) error.
            flags.dont_retry = 1;
            if (Comm::IsConnOpen(serverConn)) {
                serverConn->close();
            }
            break;
        }
    }
}

/*
 * FwdState::reforward
 *
 * returns TRUE if the transaction SHOULD be re-forwarded to the
 * next choice in the serverDestinations list.  This method is called when
 * server-side communication completes normally, or experiences
 * some error after receiving the end of HTTP headers.
 */
int
FwdState::reforward()
{
    StoreEntry *e = entry;
    http_status s;

    if (EBIT_TEST(e->flags, ENTRY_ABORTED)) {
        debugs(17, 3, HERE << "entry aborted");
        return 0;
    }

    assert(e->store_status == STORE_PENDING);
    assert(e->mem_obj);
#if URL_CHECKSUM_DEBUG

    e->mem_obj->checkUrlChecksum();
#endif

    debugs(17, 3, HERE << e->url() << "?" );

    if (!EBIT_TEST(e->flags, ENTRY_FWD_HDR_WAIT)) {
        debugs(17, 3, HERE << "No, ENTRY_FWD_HDR_WAIT isn't set");
        return 0;
    }

    if (n_tries > Config.forward_max_tries)
        return 0;

    if (request->bodyNibbled())
        return 0;

    if (serverDestinations.size() <= 1) {
        // NP: <= 1 since total count includes the recently failed one.
        debugs(17, 3, HERE << "No alternative forwarding paths left");
        return 0;
    }

    s = e->getReply()->sline.status;
    debugs(17, 3, HERE << "status " << s);
    return reforwardableStatus(s);
}

/**
 * Create "503 Service Unavailable" or "504 Gateway Timeout" error depending
 * on whether this is a validation request. RFC 2616 says that we MUST reply
 * with "504 Gateway Timeout" if validation fails and cached reply has
 * proxy-revalidate, must-revalidate or s-maxage Cache-Control directive.
 */
ErrorState *
FwdState::makeConnectingError(const err_type type) const
{
    return new ErrorState(type, request->flags.need_validation ?
                          HTTP_GATEWAY_TIMEOUT : HTTP_SERVICE_UNAVAILABLE, request);
}

static void
fwdStats(StoreEntry * s)
{
    int i;
    int j;
    storeAppendPrintf(s, "Status");

    for (j = 1; j < MAX_FWD_STATS_IDX; ++j) {
        storeAppendPrintf(s, "\ttry#%d", j);
    }

    storeAppendPrintf(s, "\n");

    for (i = 0; i <= (int) HTTP_INVALID_HEADER; ++i) {
        if (FwdReplyCodes[0][i] == 0)
            continue;

        storeAppendPrintf(s, "%3d", i);

        for (j = 0; j <= MAX_FWD_STATS_IDX; ++j) {
            storeAppendPrintf(s, "\t%d", FwdReplyCodes[j][i]);
        }

        storeAppendPrintf(s, "\n");
    }
}
