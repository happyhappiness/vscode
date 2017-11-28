void
FwdState::connectStart()
{
    const char *url = entry->url();
    int fd = -1;
    FwdServer *fs = servers;
    const char *host;
    unsigned short port;
    int ctimeout;
    int ftimeout = Config.Timeout.forward - (squid_curtime - start_t);

    IpAddress outgoing;
    unsigned short tos;
    IpAddress client_addr;
    assert(fs);
    assert(server_fd == -1);
    debugs(17, 3, "fwdConnectStart: " << url);

    if (n_tries == 0) // first attempt
        request->hier.first_conn_start = current_time;

    if (fs->_peer) {
        ctimeout = fs->_peer->connect_timeout > 0 ? fs->_peer->connect_timeout
                   : Config.Timeout.peer_connect;
    } else {
        ctimeout = Config.Timeout.connect;
    }

    if (request->flags.spoof_client_ip) {
        if (!fs->_peer || !fs->_peer->options.no_tproxy)
            client_addr = request->client_addr;
        // else no tproxy today ...
    }

    if (ftimeout < 0)
        ftimeout = 5;

    if (ftimeout < ctimeout)
        ctimeout = ftimeout;

    if (fs->_peer && request->flags.sslBumped == true) {
        debugs(50, 4, "fwdConnectStart: Ssl bumped connections through parrent proxy are not allowed");
        ErrorState *anErr = errorCon(ERR_CANNOT_FORWARD, HTTP_SERVICE_UNAVAILABLE, request);
        fail(anErr);
        self = NULL; // refcounted
        return;
    }

    request->flags.pinned = 0;
    if (fs->code == PINNED) {
        ConnStateData *pinned_connection = request->pinnedConnection();
        assert(pinned_connection);
        fd = pinned_connection->validatePinnedConnection(request, fs->_peer);
        if (fd >= 0) {
            pinned_connection->unpinConnection();
#if 0
            if (!fs->_peer)
                fs->code = HIER_DIRECT;
#endif
            server_fd = fd;
            n_tries++;
            request->flags.pinned = 1;
            if (pinned_connection->pinnedAuth())
                request->flags.auth = 1;
            comm_add_close_handler(fd, fwdServerClosedWrapper, this);
            updateHierarchyInfo();
            connectDone(fd, DnsLookupDetails(), COMM_OK, 0);
            return;
        }
        /* Failure. Fall back on next path */
        debugs(17,2,HERE << " Pinned connection " << pinned_connection << " not valid. Releasing.");
        request->releasePinnedConnection();
        servers = fs->next;
        fwdServerFree(fs);
        connectStart();
        return;
    }

    if (fs->_peer) {
        host = fs->_peer->host;
        port = fs->_peer->http_port;
        fd = fwdPconnPool->pop(fs->_peer->name, fs->_peer->http_port, request->GetHost(), client_addr, checkRetriable());
    } else {
        host = request->GetHost();
        port = request->port;
        fd = fwdPconnPool->pop(host, port, NULL, client_addr, checkRetriable());
    }
    if (fd >= 0) {
        debugs(17, 3, "fwdConnectStart: reusing pconn FD " << fd);
        server_fd = fd;
        n_tries++;

        if (!fs->_peer)
            origin_tries++;

        updateHierarchyInfo();

        comm_add_close_handler(fd, fwdServerClosedWrapper, this);

        if (comm_local_port(fd))
            request->hier.peer_local_addr = fd_table[fd].local_addr;

        dispatch();

        return;
    }

#if URL_CHECKSUM_DEBUG
    entry->mem_obj->checkUrlChecksum();
#endif

    outgoing = getOutgoingAddr(request, fs->_peer);

    // if IPv6 is disabled try to force IPv4-only outgoing.
    if (!Ip::EnableIpv6 && !outgoing.SetIPv4()) {
        debugs(50, 4, "fwdConnectStart: IPv6 is Disabled. Cannot connect from " << outgoing);
        ErrorState *anErr = errorCon(ERR_CONNECT_FAIL, HTTP_SERVICE_UNAVAILABLE, request);
        anErr->xerrno = EAFNOSUPPORT;
        fail(anErr);
        self = NULL;	// refcounted
        return;
    }

    // if IPv6 is split-stack, prefer IPv4
    if (Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK) {
        // NP: This is not a great choice of default,
        // but with the current Internet being IPv4-majority has a higher success rate.
        // if setting to IPv4 fails we dont care, that just means to use IPv6 outgoing.
        outgoing.SetIPv4();
    }

    tos = getOutgoingTOS(request);

    debugs(17, 3, "fwdConnectStart: got outgoing addr " << outgoing << ", tos " << tos);

    int commFlags = COMM_NONBLOCKING;
    if (request->flags.spoof_client_ip) {
        if (!fs->_peer || !fs->_peer->options.no_tproxy)
            commFlags |= COMM_TRANSPARENT;
        // else no tproxy today ...
    }

    fd = comm_openex(SOCK_STREAM, IPPROTO_TCP, outgoing, commFlags, tos, url);

    debugs(17, 3, "fwdConnectStart: got TCP FD " << fd);

    if (fd < 0) {
        debugs(50, 4, "fwdConnectStart: " << xstrerror());
        ErrorState *anErr = errorCon(ERR_SOCKET_FAILURE, HTTP_INTERNAL_SERVER_ERROR, request);
        anErr->xerrno = errno;
        fail(anErr);
        self = NULL;	// refcounted
        return;
    }

    server_fd = fd;
    n_tries++;

    if (!fs->_peer)
        origin_tries++;

    if (comm_local_port(fd))
        request->hier.peer_local_addr = fd_table[fd].local_addr;

    /*
     * stats.conn_open is used to account for the number of
     * connections that we have open to the peer, so we can limit
     * based on the max-conn option.  We need to increment here,
     * even if the connection may fail.
     */

    if (fs->_peer) {
        fs->_peer->stats.conn_open++;
        comm_add_close_handler(fd, fwdPeerClosed, fs->_peer);
    }

    comm_add_close_handler(fd, fwdServerClosedWrapper, this);

    commSetTimeout(fd, ctimeout, fwdConnectTimeoutWrapper, this);

#if LINUX_TPROXY2
    if (!fs->_peer && request->flags.spoof_client_ip) {
        // try to set the outgoing address using TPROXY v2
        // if it fails we abort any further TPROXY actions on this connection
        if (IpInterceptor.SetTproxy2OutgoingAddr(fd, src) == -1) {
            request->flags.spoof_client_ip = 0;
        }
    }
#endif

    updateHierarchyInfo();
    commConnectStart(fd, host, port, fwdConnectDoneWrapper, this);
}