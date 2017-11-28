void
ClientHttpRequest::sslBumpEstablish(Comm::Flag errflag)
{
    // Bail out quickly on Comm::ERR_CLOSING - close handlers will tidy up
    if (errflag == Comm::ERR_CLOSING)
        return;

    if (errflag) {
        debugs(85, 3, HERE << "CONNECT response failure in SslBump: " << errflag);
        getConn()->clientConnection->close();
        return;
    }

    // We lack HttpReply which logRequest() uses to log the status code.
    // TODO: Use HttpReply instead of the "200 Connection established" string.
    al->http.code = 200;

#if USE_AUTH
    // Preserve authentication info for the ssl-bumped request
    if (request->auth_user_request != NULL)
        getConn()->setAuth(request->auth_user_request, "SSL-bumped CONNECT");
#endif

    assert(sslBumpNeeded());
    getConn()->switchToHttps(request, sslBumpNeed_);
}