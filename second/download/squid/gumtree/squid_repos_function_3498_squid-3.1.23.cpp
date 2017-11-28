void
httpAccept(int sock, int newfd, ConnectionDetail *details,
           comm_err_t flag, int xerrno, void *data)
{
    http_port_list *s = (http_port_list *)data;
    ConnStateData *connState = NULL;

    if (flag == COMM_ERR_CLOSING) {
        return;
    }

    if (!okToAccept())
        AcceptLimiter::Instance().defer (sock, httpAccept, data);
    else
        /* kick off another one for later */
        comm_accept(sock, httpAccept, data);

    if (flag != COMM_OK) {
        debugs(33, 1, "httpAccept: FD " << sock << ": accept failure: " << xstrerr(xerrno));
        return;
    }

    debugs(33, 4, "httpAccept: FD " << newfd << ": accepted");
    fd_note(newfd, "client http connect");
    connState = connStateCreate(&details->peer, &details->me, newfd, s);

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

    if (s->tcp_keepalive.enabled) {
        commSetTcpKeepalive(newfd, s->tcp_keepalive.idle, s->tcp_keepalive.interval, s->tcp_keepalive.timeout);
    }

    connState->readSomeData();

    clientdbEstablished(details->peer, 1);

    incoming_sockets_accepted++;
}