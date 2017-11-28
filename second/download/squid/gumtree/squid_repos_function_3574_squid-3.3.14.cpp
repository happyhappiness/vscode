void
ConnStateData::switchToHttps(HttpRequest *request, Ssl::BumpMode bumpServerMode)
{
    assert(!switchedToHttps_);

    sslConnectHostOrIp = request->GetHost();
    sslCommonName = request->GetHost();

    // We are going to read new request
    flags.readMore = true;
    debugs(33, 5, HERE << "converting " << clientConnection << " to SSL");

    // If sslServerBump is set, then we have decided to deny CONNECT
    // and now want to switch to SSL to send the error to the client
    // without even peeking at the origin server certificate.
    if (bumpServerMode == Ssl::bumpServerFirst && !sslServerBump) {
        request->flags.sslPeek = 1;
        sslServerBump = new Ssl::ServerBump(request);

        // will call httpsPeeked() with certificate and connection, eventually
        FwdState::fwdStart(clientConnection, sslServerBump->entry, sslServerBump->request);
        return;
    }

    // otherwise, use sslConnectHostOrIp
    getSslContextStart();
}