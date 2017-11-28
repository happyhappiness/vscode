void
Ssl::PeerConnector::serverCertificateVerified()
{
    if (ConnStateData *csd = request->clientConnectionManager.valid()) {
        Ssl::X509_Pointer serverCert;
        if(Ssl::ServerBump *serverBump = csd->serverBump())
            serverCert.resetAndLock(serverBump->serverCert.get());
        else {
            const int fd = serverConnection()->fd;
            SSL *ssl = fd_table[fd].ssl;
            serverCert.reset(SSL_get_peer_certificate(ssl));
        }
        if (serverCert.get()) {
            csd->resetSslCommonName(Ssl::CommonHostName(serverCert.get()));
            debugs(83, 5, "HTTPS server CN: " << csd->sslCommonName() <<
                   " bumped: " << *serverConnection());
        }
    }
}