void
ConnStateData::switchToHttps(HttpRequest *request, Ssl::BumpMode bumpServerMode)
{
    assert(!switchedToHttps_);

    sslConnectHostOrIp = request->url.host();
    resetSslCommonName(request->url.host());

    // We are going to read new request
    flags.readMore = true;
    debugs(33, 5, HERE << "converting " << clientConnection << " to SSL");

    // keep version major.minor details the same.
    // but we are now performing the HTTPS handshake traffic
    transferProtocol.protocol = AnyP::PROTO_HTTPS;

    // If sslServerBump is set, then we have decided to deny CONNECT
    // and now want to switch to SSL to send the error to the client
    // without even peeking at the origin server certificate.
    if (bumpServerMode == Ssl::bumpServerFirst && !sslServerBump) {
        request->flags.sslPeek = true;
        sslServerBump = new Ssl::ServerBump(request);
    } else if (bumpServerMode == Ssl::bumpPeek || bumpServerMode == Ssl::bumpStare) {
        request->flags.sslPeek = true;
        sslServerBump = new Ssl::ServerBump(request, NULL, bumpServerMode);
    }

    // commSetConnTimeout() was called for this request before we switched.
    // Fix timeout to request_start_timeout
    typedef CommCbMemFunT<ConnStateData, CommTimeoutCbParams> TimeoutDialer;
    AsyncCall::Pointer timeoutCall =  JobCallback(33, 5,
                                      TimeoutDialer, this, ConnStateData::requestTimeout);
    commSetConnTimeout(clientConnection, Config.Timeout.request_start_timeout, timeoutCall);
    // Also reset receivedFirstByte_ flag to allow this timeout work in the case we have
    // a bumbed "connect" request on non transparent port.
    receivedFirstByte_ = false;
    // Get more data to peek at Tls
    parsingTlsHandshake = true;
    readSomeData();
}