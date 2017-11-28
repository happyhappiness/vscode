bool
ConnStateData::fakeAConnectRequest(const char *reason, const SBuf &payload)
{
    debugs(33, 2, "fake a CONNECT request to force connState to tunnel for " << reason);

    SBuf connectHost;
    assert(transparent());
    const unsigned short connectPort = clientConnection->local.port();

#if USE_OPENSSL
    if (!tlsClientSni_.isEmpty())
        connectHost.assign(tlsClientSni_);
    else
#endif
    {
        static char ip[MAX_IPSTRLEN];
        clientConnection->local.toHostStr(ip, sizeof(ip));
        connectHost.assign(ip);
    }

    ClientHttpRequest *http = buildFakeRequest(Http::METHOD_CONNECT, connectHost, connectPort, payload);

    http->calloutContext = new ClientRequestContext(http);
    HttpRequest::Pointer request = http->request;
    http->doCallouts();
    clientProcessRequestFinished(this, request);
    return true;
}