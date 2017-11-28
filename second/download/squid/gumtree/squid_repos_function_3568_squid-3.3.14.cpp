static void
httpsAccept(const CommAcceptCbParams &params)
{
    AnyP::PortCfg *s = static_cast<AnyP::PortCfg *>(params.data);

    if (params.flag != COMM_OK) {
        // Its possible the call was still queued when the client disconnected
        debugs(33, 2, "httpsAccept: " << s->listenConn << ": accept failure: " << xstrerr(params.xerrno));
        return;
    }

    debugs(33, 4, HERE << params.conn << " accepted, starting SSL negotiation.");
    fd_note(params.conn->fd, "client https connect");

    if (s->tcp_keepalive.enabled) {
        commSetTcpKeepalive(params.conn->fd, s->tcp_keepalive.idle, s->tcp_keepalive.interval, s->tcp_keepalive.timeout);
    }

    ++incoming_sockets_accepted;

    // Socket is ready, setup the connection manager to start using it
    ConnStateData *connState = connStateCreate(params.conn, s);

    if (s->sslBump) {
        debugs(33, 5, "httpsAccept: accept transparent connection: " << params.conn);

        if (!Config.accessList.ssl_bump) {
            httpsSslBumpAccessCheckDone(ACCESS_DENIED, connState);
            return;
        }

        // Create a fake HTTP request for ssl_bump ACL check,
        // using tproxy/intercept provided destination IP and port.
        HttpRequest *request = new HttpRequest();
        static char ip[MAX_IPSTRLEN];
        assert(params.conn->flags & (COMM_TRANSPARENT | COMM_INTERCEPTION));
        request->SetHost(params.conn->local.NtoA(ip, sizeof(ip)));
        request->port = params.conn->local.GetPort();
        request->myportname = s->name;

        ACLFilledChecklist *acl_checklist = new ACLFilledChecklist(Config.accessList.ssl_bump, request, NULL);
        acl_checklist->src_addr = params.conn->remote;
        acl_checklist->my_addr = s->s;
        acl_checklist->nonBlockingCheck(httpsSslBumpAccessCheckDone, connState);
        return;
    } else {
        SSL_CTX *sslContext = s->staticSslContext.get();
        httpsEstablish(connState, sslContext, Ssl::bumpNone);
    }
}