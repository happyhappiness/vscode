void
httpAccept(const CommAcceptCbParams &params)
{
    AnyP::PortCfg *s = static_cast<AnyP::PortCfg *>(params.data);

    if (params.flag != COMM_OK) {
        // Its possible the call was still queued when the client disconnected
        debugs(33, 2, "httpAccept: " << s->listenConn << ": accept failure: " << xstrerr(params.xerrno));
        return;
    }

    debugs(33, 4, HERE << params.conn << ": accepted");
    fd_note(params.conn->fd, "client http connect");

    if (s->tcp_keepalive.enabled) {
        commSetTcpKeepalive(params.conn->fd, s->tcp_keepalive.idle, s->tcp_keepalive.interval, s->tcp_keepalive.timeout);
    }

    ++ incoming_sockets_accepted;

    // Socket is ready, setup the connection manager to start using it
    ConnStateData *connState = connStateCreate(params.conn, s);

    typedef CommCbMemFunT<ConnStateData, CommTimeoutCbParams> TimeoutDialer;
    AsyncCall::Pointer timeoutCall =  JobCallback(33, 5,
                                      TimeoutDialer, connState, ConnStateData::requestTimeout);
    commSetConnTimeout(params.conn, Config.Timeout.request, timeoutCall);

    connState->readSomeData();

#if USE_DELAY_POOLS
    fd_table[params.conn->fd].clientInfo = NULL;

    if (Config.onoff.client_db) {
        /* it was said several times that client write limiter does not work if client_db is disabled */

        ClientDelayPools& pools(Config.ClientDelay.pools);
        ACLFilledChecklist ch(NULL, NULL, NULL);

        // TODO: we check early to limit error response bandwith but we
        // should recheck when we can honor delay_pool_uses_indirect
        // TODO: we should also pass the port details for myportname here.
        ch.src_addr = params.conn->remote;
        ch.my_addr = params.conn->local;

        for (unsigned int pool = 0; pool < pools.size(); ++pool) {

            /* pools require explicit 'allow' to assign a client into them */
            if (pools[pool].access) {
                ch.accessList = pools[pool].access;
                allow_t answer = ch.fastCheck();
                if (answer == ACCESS_ALLOWED) {

                    /*  request client information from db after we did all checks
                        this will save hash lookup if client failed checks */
                    ClientInfo * cli = clientdbGetInfo(params.conn->remote);
                    assert(cli);

                    /* put client info in FDE */
                    fd_table[params.conn->fd].clientInfo = cli;

                    /* setup write limiter for this request */
                    const double burst = floor(0.5 +
                                               (pools[pool].highwatermark * Config.ClientDelay.initial)/100.0);
                    cli->setWriteLimiter(pools[pool].rate, burst, pools[pool].highwatermark);
                    break;
                } else {
                    debugs(83, 4, HERE << "Delay pool " << pool << " skipped because ACL " << answer);
                }
            }
        }
    }
#endif
}