void
Ssl::PeerConnector::handleServerCertificate()
{
    if (serverCertificateHandled)
        return;

    if (ConnStateData *csd = request->clientConnectionManager.valid()) {
        const int fd = serverConnection()->fd;
        SSL *ssl = fd_table[fd].ssl;
        Ssl::X509_Pointer serverCert(SSL_get_peer_certificate(ssl));
        if (!serverCert.get())
            return;

        serverCertificateHandled = true;

        // remember the server certificate for later use
        if (Ssl::ServerBump *serverBump = csd->serverBump()) {
            serverBump->serverCert.reset(serverCert.release());
        }
    }
}