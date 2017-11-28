static void
tunnelConnectDone(const Comm::ConnectionPointer &conn, Comm::Flag status, int xerrno, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;

    if (status != Comm::OK) {
        debugs(26, 4, HERE << conn << ", comm failure recovery.");
        /* At this point only the TCP handshake has failed. no data has been passed.
         * we are allowed to re-try the TCP-level connection to alternate IPs for CONNECT.
         */
        debugs(26, 4, "removing server 1 of " << tunnelState->serverDestinations.size() <<
               " from destinations (" << tunnelState->serverDestinations[0] << ")");
        tunnelState->serverDestinations.erase(tunnelState->serverDestinations.begin());
        time_t fwdTimeout = tunnelState->started + Config.Timeout.forward;
        if (fwdTimeout > squid_curtime && tunnelState->serverDestinations.size() > 0) {
            // find remaining forward_timeout available for this attempt
            fwdTimeout -= squid_curtime;
            if (fwdTimeout > Config.Timeout.connect)
                fwdTimeout = Config.Timeout.connect;
            /* Try another IP of this destination host */
            GetMarkingsToServer(tunnelState->request.getRaw(), *tunnelState->serverDestinations[0]);
            debugs(26, 4, HERE << "retry with : " << tunnelState->serverDestinations[0]);
            AsyncCall::Pointer call = commCbCall(26,3, "tunnelConnectDone", CommConnectCbPtrFun(tunnelConnectDone, tunnelState));
            Comm::ConnOpener *cs = new Comm::ConnOpener(tunnelState->serverDestinations[0], call, fwdTimeout);
            cs->setHost(tunnelState->url);
            AsyncJob::Start(cs);
        } else {
            debugs(26, 4, HERE << "terminate with error.");
            ErrorState *err = new ErrorState(ERR_CONNECT_FAIL, Http::scServiceUnavailable, tunnelState->request.getRaw());
            *tunnelState->status_ptr = Http::scServiceUnavailable;
            err->xerrno = xerrno;
            // on timeout is this still:    err->xerrno = ETIMEDOUT;
            err->port = conn->remote.port();
            err->callback = tunnelErrorComplete;
            err->callback_data = tunnelState;
            errorSend(tunnelState->client.conn, err);
            if (tunnelState->request != NULL)
                tunnelState->request->hier.stopPeerClock(false);
        }
        return;
    }

#if USE_DELAY_POOLS
    /* no point using the delayIsNoDelay stuff since tunnel is nice and simple */
    if (conn->getPeer() && conn->getPeer()->options.no_delay)
        tunnelState->server.setDelayId(DelayId());
#endif

    tunnelState->request->hier.note(conn, tunnelState->getHost());

    tunnelState->server.conn = conn;
    tunnelState->request->peer_host = conn->getPeer() ? conn->getPeer()->host : NULL;
    comm_add_close_handler(conn->fd, tunnelServerClosed, tunnelState);

    debugs(26, 4, HERE << "determine post-connect handling pathway.");
    if (conn->getPeer()) {
        tunnelState->request->peer_login = conn->getPeer()->login;
        tunnelState->request->peer_domain = conn->getPeer()->domain;
        tunnelState->request->flags.proxying = !(conn->getPeer()->options.originserver);
    } else {
        tunnelState->request->peer_login = NULL;
        tunnelState->request->peer_domain = NULL;
        tunnelState->request->flags.proxying = false;
    }

    if (tunnelState->request->flags.proxying)
        tunnelState->connectToPeer();
    else {
        tunnelConnected(conn, tunnelState);
    }

    AsyncCall::Pointer timeoutCall = commCbCall(5, 4, "tunnelTimeout",
                                     CommTimeoutCbPtrFun(tunnelTimeout, tunnelState));
    commSetConnTimeout(conn, Config.Timeout.read, timeoutCall);
}