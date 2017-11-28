void
FwdState::dispatch()
{
    debugs(17, 3, clientConn << ": Fetching " << request->method << ' ' << entry->url());
    /*
     * Assert that server_fd is set.  This is to guarantee that fwdState
     * is attached to something and will be deallocated when server_fd
     * is closed.
     */
    assert(Comm::IsConnOpen(serverConn));

    fd_note(serverConnection()->fd, entry->url());

    fd_table[serverConnection()->fd].noteUse();

    /*assert(!EBIT_TEST(entry->flags, ENTRY_DISPATCHED)); */
    assert(entry->ping_status != PING_WAITING);

    assert(entry->locked());

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

#if USE_OPENSSL
    if (request->flags.sslPeek) {
        CallJobHere1(17, 4, request->clientConnectionManager, ConnStateData,
                     ConnStateData::httpsPeeked, ConnStateData::PinnedIdleContext(serverConnection(), request));
        unregister(serverConn); // async call owns it now
        complete(); // destroys us
        return;
    }
#endif

    if (serverConnection()->getPeer() != NULL) {
        ++ serverConnection()->getPeer()->stats.fetches;
        request->peer_login = serverConnection()->getPeer()->login;
        request->peer_domain = serverConnection()->getPeer()->domain;
        httpStart(this);
    } else {
        assert(!request->flags.sslPeek);
        request->peer_login = NULL;
        request->peer_domain = NULL;

        switch (request->url.getScheme()) {
#if USE_OPENSSL

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
            if (request->flags.ftpNative)
                Ftp::StartRelay(this);
            else
                Ftp::StartGateway(this);
            break;

        case AnyP::PROTO_CACHE_OBJECT:

        case AnyP::PROTO_URN:
            fatal_dump("Should never get here");
            break;

        case AnyP::PROTO_WHOIS:
            whoisStart(this);
            break;

        case AnyP::PROTO_WAIS:  /* Not implemented */

        default:
            debugs(17, DBG_IMPORTANT, "WARNING: Cannot retrieve '" << entry->url() << "'.");
            ErrorState *anErr = new ErrorState(ERR_UNSUP_REQ, Http::scBadRequest, request);
            fail(anErr);
            // Set the dont_retry flag because this is not a transient (network) error.
            flags.dont_retry = true;
            if (Comm::IsConnOpen(serverConn)) {
                serverConn->close();
            }
            break;
        }
    }
}