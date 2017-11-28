void
Ssl::PeekingPeerConnector::noteNegotiationDone(ErrorState *error)
{
    // Check the list error with
    if (!request->clientConnectionManager.valid() || !fd_table[serverConnection()->fd].ssl)
        return;

    // remember the server certificate from the ErrorDetail object
    if (Ssl::ServerBump *serverBump = request->clientConnectionManager->serverBump()) {
        if (!serverBump->serverCert.get()) {
            // remember the server certificate from the ErrorDetail object
            if (error && error->detail && error->detail->peerCert())
                serverBump->serverCert.resetAndLock(error->detail->peerCert());
            else {
                handleServerCertificate();
            }
        }

        if (error) {
            // For intercepted connections, set the host name to the server
            // certificate CN. Otherwise, we just hope that CONNECT is using
            // a user-entered address (a host name or a user-entered IP).
            const bool isConnectRequest = !request->clientConnectionManager->port->flags.isIntercepted();
            if (request->flags.sslPeek && !isConnectRequest) {
                if (X509 *srvX509 = serverBump->serverCert.get()) {
                    if (const char *name = Ssl::CommonHostName(srvX509)) {
                        request->url.host(name);
                        debugs(83, 3, "reset request host: " << name);
                    }
                }
            }
        }
    }

    if (!error) {
        serverCertificateVerified();
        if (splice) {
            switchToTunnel(request.getRaw(), clientConn, serverConn);
            tunnelInsteadOfNegotiating();
        }
    }
}