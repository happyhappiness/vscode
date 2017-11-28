static void
tunnelConnectDone(const Comm::ConnectionPointer &conn, comm_err_t status, int xerrno, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;

    if (status != COMM_OK) {
        debugs(26, 4, HERE << conn << ", comm failure recovery.");
        /* At this point only the TCP handshake has failed. no data has been passed.
         * we are allowed to re-try the TCP-level connection to alternate IPs for CONNECT.
         */
        tunnelState->serverDestinations.shift();
        if (status != COMM_TIMEOUT && tunnelState->serverDestinations.size() > 0) {
            /* Try another IP of this destination host */

            if (Ip::Qos::TheConfig.isAclTosActive()) {
                tunnelState->serverDestinations[0]->tos = GetTosToServer(tunnelState->request);
            }

#if SO_MARK && USE_LIBCAP
            tunnelState->serverDestinations[0]->nfmark = GetNfmarkToServer(tunnelState->request);
#endif

            debugs(26, 4, HERE << "retry with : " << tunnelState->serverDestinations[0]);
            AsyncCall::Pointer call = commCbCall(26,3, "tunnelConnectDone", CommConnectCbPtrFun(tunnelConnectDone, tunnelState));
            Comm::ConnOpener *cs = new Comm::ConnOpener(tunnelState->serverDestinations[0], call, Config.Timeout.connect);
            cs->setHost(tunnelState->url);
            AsyncJob::Start(cs);
        } else {
            debugs(26, 4, HERE << "terminate with error.");
            ErrorState *err = new ErrorState(ERR_CONNECT_FAIL, HTTP_SERVICE_UNAVAILABLE, tunnelState->request);
            *tunnelState->status_ptr = HTTP_SERVICE_UNAVAILABLE;
            err->xerrno = xerrno;
            // on timeout is this still:    err->xerrno = ETIMEDOUT;
            err->port = conn->remote.GetPort();
            err->callback = tunnelErrorComplete;
            err->callback_data = tunnelState;
            errorSend(tunnelState->client.conn, err);
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
        tunnelState->request->flags.proxying = (conn->getPeer()->options.originserver?0:1);
    } else {
        tunnelState->request->peer_login = NULL;
        tunnelState->request->flags.proxying = 0;
    }

    if (tunnelState->request->flags.proxying)
        tunnelRelayConnectRequest(conn, tunnelState);
    else {
        tunnelConnected(conn, tunnelState);
    }

    AsyncCall::Pointer timeoutCall = commCbCall(5, 4, "tunnelTimeout",
                                     CommTimeoutCbPtrFun(tunnelTimeout, tunnelState));
    commSetConnTimeout(conn, Config.Timeout.read, timeoutCall);
}