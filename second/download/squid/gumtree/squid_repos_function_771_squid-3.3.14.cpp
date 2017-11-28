void
ClientHttpRequest::sslBumpStart()
{
    debugs(85, 5, HERE << "Confirming " << Ssl::bumpMode(sslBumpNeed_) <<
           "-bumped CONNECT tunnel on FD " << getConn()->clientConnection);
    getConn()->sslBumpMode = sslBumpNeed_;

    // send an HTTP 200 response to kick client SSL negotiation
    // TODO: Unify with tunnel.cc and add a Server(?) header
    static const char *const conn_established = "HTTP/1.1 200 Connection established\r\n\r\n";
    AsyncCall::Pointer call = commCbCall(85, 5, "ClientSocketContext::sslBumpEstablish",
                                         CommIoCbPtrFun(&SslBumpEstablish, this));
    Comm::Write(getConn()->clientConnection, conn_established, strlen(conn_established), call, NULL);
}