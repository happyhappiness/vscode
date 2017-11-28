        bumpAction = (Ssl::BumpMode)answer.kind;
    } else
        bumpAction = Ssl::bumpSplice;

    connState->serverBump()->act.step2 = bumpAction;
    connState->sslBumpMode = bumpAction;

    if (bumpAction == Ssl::bumpTerminate) {
        connState->clientConnection->close();
    } else if (bumpAction != Ssl::bumpSplice) {
        connState->startPeekAndSpliceDone();
    } else {
        //Normally we can splice here, because we just got client hello message
        SSL *ssl = fd_table[connState->clientConnection->fd].ssl;
        BIO *b = SSL_get_rbio(ssl);
        Ssl::ClientBio *bio = static_cast<Ssl::ClientBio *>(b->ptr);
        MemBuf const &rbuf = bio->rBufData();
        debugs(83,5, "Bio for  " << connState->clientConnection << " read " << rbuf.contentSize() << " helo bytes");
        // Do splice:
        fd_table[connState->clientConnection->fd].read_method = &default_read_method;
        fd_table[connState->clientConnection->fd].write_method = &default_write_method;

        ClientSocketContext::Pointer context = connState->getCurrentContext();
        Must(context != NULL);
        if (connState->transparent()) {
            // If we are going to fake the second CONNECT, clear the first one.
            context->connIsFinished();

            // fake a CONNECT request to force connState to tunnel
            // XXX: copy from MemBuf reallocates, not a regression since old code did too
            SBuf temp;
            temp.append(rbuf.content(), rbuf.contentSize());
            connState->fakeAConnectRequest("intercepted TLS spliced", temp);
        } else {
            // in.buf still has the "CONNECT ..." request data, reset it to SSL hello message
            connState->in.buf.append(rbuf.content(), rbuf.contentSize());
            ClientHttpRequest *http = context->http;
            tunnelStart(http);
        }
    }
}

void
ConnStateData::startPeekAndSpliceDone()
{
    // This is the Step2 of the SSL bumping
    assert(sslServerBump);
    if (sslServerBump->step == Ssl::bumpStep1) {
        sslServerBump->step = Ssl::bumpStep2;
        // Run a accessList check to check if want to splice or continue bumping

        ACLFilledChecklist *acl_checklist = new ACLFilledChecklist(Config.accessList.ssl_bump, sslServerBump->request.getRaw(), NULL);
        //acl_checklist->src_addr = params.conn->remote;
        //acl_checklist->my_addr = s->s;
        acl_checklist->banAction(allow_t(ACCESS_ALLOWED, Ssl::bumpNone));
        acl_checklist->banAction(allow_t(ACCESS_ALLOWED, Ssl::bumpClientFirst));
        acl_checklist->banAction(allow_t(ACCESS_ALLOWED, Ssl::bumpServerFirst));
        acl_checklist->nonBlockingCheck(httpsSslBumpStep2AccessCheckDone, this);
        return;
    }

    FwdState::fwdStart(clientConnection, sslServerBump->entry, sslServerBump->request.getRaw());
}

void
ConnStateData::doPeekAndSpliceStep()
{
    SSL *ssl = fd_table[clientConnection->fd].ssl;
    BIO *b = SSL_get_rbio(ssl);
    assert(b);
    Ssl::ClientBio *bio = static_cast<Ssl::ClientBio *>(b->ptr);

    debugs(33, 5, "PeekAndSplice mode, proceed with client negotiation. Currrent state:" << SSL_state_string_long(ssl));
    bio->hold(false);

    Comm::SetSelect(clientConnection->fd, COMM_SELECT_WRITE, clientNegotiateSSL, this, 0);
    switchedToHttps_ = true;
}

void
ConnStateData::httpsPeeked(PinnedIdleContext pic)
{
    Must(sslServerBump != NULL);
    Must(sslServerBump->request == pic.request);
    Must(currentobject == NULL || currentobject->http == NULL || currentobject->http->request == pic.request.getRaw());

    if (Comm::IsConnOpen(pic.connection)) {
        notePinnedConnectionBecameIdle(pic);

        debugs(33, 5, HERE << "bumped HTTPS server: " << sslConnectHostOrIp);
    } else
        debugs(33, 5, HERE << "Error while bumping: " << sslConnectHostOrIp);

    getSslContextStart();
}

#endif /* USE_OPENSSL */

void
ConnStateData::fakeAConnectRequest(const char *reason, const SBuf &payload)
{
    // fake a CONNECT request to force connState to tunnel
    SBuf connectHost;
#if USE_OPENSSL
    if (serverBump() && !serverBump()->clientSni.isEmpty()) {
        connectHost.assign(serverBump()->clientSni);
        if (clientConnection->local.port() > 0)
            connectHost.appendf(":%d",clientConnection->local.port());
    } else
#endif
    {
        static char ip[MAX_IPSTRLEN];
        connectHost.assign(clientConnection->local.toUrl(ip, sizeof(ip)));
    }
    // Pre-pend this fake request to the TLS bits already in the buffer
    SBuf retStr;
    retStr.append("CONNECT ");
    retStr.append(connectHost);
    retStr.append(" HTTP/1.1\r\nHost: ");
    retStr.append(connectHost);
    retStr.append("\r\n\r\n");
    retStr.append(payload);
    in.buf = retStr;
    bool ret = handleReadData();
    if (ret)
        ret = clientParseRequests();

    if (!ret) {
        debugs(33, 2, "Failed to start fake CONNECT request for " << reason << " connection: " << clientConnection);
        clientConnection->close();
    }
}

/// check FD after clientHttp[s]ConnectionOpened, adjust HttpSockets as needed
static bool
OpenedHttpSocket(const Comm::ConnectionPointer &c, const Ipc::FdNoteId portType)
{
