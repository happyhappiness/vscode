static void
httpsAccept(int sock, int newfd, ConnectionDetail *details,
            comm_err_t flag, int xerrno, void *data)
{
    https_port_list *s = (https_port_list *)data;
    SSL_CTX *sslContext = s->staticSslContext.get();

    if (flag == COMM_ERR_CLOSING) {
        return;
    }

    if (!okToAccept())
        AcceptLimiter::Instance().defer (sock, httpsAccept, data);
    else
        /* kick off another one for later */
        comm_accept(sock, httpsAccept, data);

    if (flag != COMM_OK) {
        errno = xerrno;
        debugs(33, 1, "httpsAccept: FD " << sock << ": accept failure: " << xstrerr(xerrno));
        return;
    }

    SSL *ssl = NULL;
    if (!(ssl = httpsCreate(newfd, details, sslContext)))
        return;

    debugs(33, 5, "httpsAccept: FD " << newfd << " accepted, starting SSL negotiation.");
    fd_note(newfd, "client https connect");
    ConnStateData *connState = connStateCreate(details->peer, details->me,
                               newfd, &s->http);
    typedef CommCbMemFunT<ConnStateData, CommCloseCbParams> Dialer;
    AsyncCall::Pointer call = JobCallback(33, 5,
                                          Dialer, connState, ConnStateData::connStateClosed);
    comm_add_close_handler(newfd, call);

    if (Config.onoff.log_fqdn)
        fqdncache_gethostbyaddr(details->peer, FQDN_LOOKUP_IF_MISS);

    typedef CommCbMemFunT<ConnStateData, CommTimeoutCbParams> TimeoutDialer;
    AsyncCall::Pointer timeoutCall =  JobCallback(33, 5,
                                      TimeoutDialer, connState, ConnStateData::requestTimeout);
    commSetTimeout(newfd, Config.Timeout.request, timeoutCall);

#if USE_IDENT
    if (Ident::TheConfig.identLookup) {
        ACLFilledChecklist identChecklist(Ident::TheConfig.identLookup, NULL, NULL);
        identChecklist.src_addr = details->peer;
        identChecklist.my_addr = details->me;
        if (identChecklist.fastCheck())
            Ident::Start(details->me, details->peer, clientIdentDone, connState);
    }

#endif

    if (s->http.tcp_keepalive.enabled) {
        commSetTcpKeepalive(newfd, s->http.tcp_keepalive.idle, s->http.tcp_keepalive.interval, s->http.tcp_keepalive.timeout);
    }

    commSetSelect(newfd, COMM_SELECT_READ, clientNegotiateSSL, connState, 0);

    clientdbEstablished(details->peer, 1);

    incoming_sockets_accepted++;
}