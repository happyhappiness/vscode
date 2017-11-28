void
Ssl::PeekingPeerConnector::handleServerCertificate()
{
    if (serverCertificateHandled)
        return;

    if (ConnStateData *csd = request->clientConnectionManager.valid()) {
        const int fd = serverConnection()->fd;
        Security::SessionPointer session(fd_table[fd].ssl);
        Security::CertPointer serverCert(SSL_get_peer_certificate(session.get()));
        if (!serverCert)
            return;

        serverCertificateHandled = true;

        // remember the server certificate for later use
        if (Ssl::ServerBump *serverBump = csd->serverBump()) {
            serverBump->serverCert = std::move(serverCert);
        }
    }
}