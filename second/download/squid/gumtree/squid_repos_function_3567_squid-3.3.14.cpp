static void
httpsSslBumpAccessCheckDone(allow_t answer, void *data)
{
    ConnStateData *connState = (ConnStateData *) data;

    // if the connection is closed or closing, just return.
    if (!connState->isOpen())
        return;

    // Require both a match and a positive bump mode to work around exceptional
    // cases where ACL code may return ACCESS_ALLOWED with zero answer.kind.
    if (answer == ACCESS_ALLOWED && answer.kind != Ssl::bumpNone) {
        debugs(33, 2, HERE << "sslBump needed for " << connState->clientConnection);
        connState->sslBumpMode = static_cast<Ssl::BumpMode>(answer.kind);
        httpsEstablish(connState, NULL, (Ssl::BumpMode)answer.kind);
    } else {
        debugs(33, 2, HERE << "sslBump not needed for " << connState->clientConnection);
        connState->sslBumpMode = Ssl::bumpNone;

        // fake a CONNECT request to force connState to tunnel
        static char ip[MAX_IPSTRLEN];
        static char reqStr[MAX_IPSTRLEN + 80];
        connState->clientConnection->local.ToURL(ip, sizeof(ip));
        snprintf(reqStr, sizeof(reqStr), "CONNECT %s HTTP/1.1\r\nHost: %s\r\n\r\n", ip, ip);
        bool ret = connState->handleReadData(reqStr, strlen(reqStr));
        if (ret)
            ret = connState->clientParseRequests();

        if (!ret) {
            debugs(33, 2, HERE << "Failed to start fake CONNECT request for ssl bumped connection: " << connState->clientConnection);
            connState->clientConnection->close();
        }
    }
}