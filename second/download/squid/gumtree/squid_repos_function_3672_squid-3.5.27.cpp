void
ConnStateData::fakeAConnectRequest(const char *reason, const SBuf &payload)
{
    // fake a CONNECT request to force connState to tunnel
    SBuf connectHost;
#if USE_OPENSSL
    if (serverBump() && !serverBump()->clientSni.isEmpty()) {
        connectHost.assign(serverBump()->clientSni);
        if (clientConnection->local.port() > 0)
            connectHost.appendf(":%d",clientConnection->local.port());
    } else
#endif
    {
        static char ip[MAX_IPSTRLEN];
        connectHost.assign(clientConnection->local.toUrl(ip, sizeof(ip)));
    }
    // Pre-pend this fake request to the TLS bits already in the buffer
    SBuf retStr;
    retStr.append("CONNECT ");
    retStr.append(connectHost);
    retStr.append(" HTTP/1.1\r\nHost: ");
    retStr.append(connectHost);
    retStr.append("\r\n\r\n");
    retStr.append(payload);
    in.buf = retStr;
    bool ret = handleReadData();
    if (ret)
        ret = clientParseRequests();

    if (!ret) {
        debugs(33, 2, "Failed to start fake CONNECT request for " << reason << " connection: " << clientConnection);
        clientConnection->close();
    }
}