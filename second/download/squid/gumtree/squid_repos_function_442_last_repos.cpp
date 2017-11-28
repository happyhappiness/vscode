void
ClientHttpRequest::sslBumpStart()
{
    debugs(85, 5, HERE << "Confirming " << Ssl::bumpMode(sslBumpNeed_) <<
           "-bumped CONNECT tunnel on FD " << getConn()->clientConnection);
    getConn()->sslBumpMode = sslBumpNeed_;

    AsyncCall::Pointer bumpCall = commCbCall(85, 5, "ClientSocketContext::sslBumpEstablish",
                                  CommIoCbPtrFun(&SslBumpEstablish, this));

    if (request->flags.interceptTproxy || request->flags.intercepted) {
        CommIoCbParams &params = GetCommParams<CommIoCbParams>(bumpCall);
        params.flag = Comm::OK;
        params.conn = getConn()->clientConnection;
        ScheduleCallHere(bumpCall);
        return;
    }

    // send an HTTP 200 response to kick client SSL negotiation
    // TODO: Unify with tunnel.cc and add a Server(?) header
    static const char *const conn_established = "HTTP/1.1 200 Connection established\r\n\r\n";
    Comm::Write(getConn()->clientConnection, conn_established, strlen(conn_established), bumpCall, NULL);
}