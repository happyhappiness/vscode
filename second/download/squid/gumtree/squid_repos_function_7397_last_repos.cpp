void
Security::PeerConnector::noteWantRead()
{
    const int fd = serverConnection()->fd;
    debugs(83, 5, serverConnection());
#if USE_OPENSSL
    Security::SessionPointer session(fd_table[fd].ssl);
    BIO *b = SSL_get_rbio(session.get());
    Ssl::ServerBio *srvBio = static_cast<Ssl::ServerBio *>(BIO_get_data(b));
    if (srvBio->holdRead()) {
        if (srvBio->gotHello()) {
            if (checkForMissingCertificates())
                return; // Wait to download certificates before proceed.

            srvBio->holdRead(false);
            // schedule a negotiateSSl to allow openSSL parse received data
            Security::PeerConnector::NegotiateSsl(fd, this);
            return;
        } else if (srvBio->gotHelloFailed()) {
            srvBio->holdRead(false);
            debugs(83, DBG_IMPORTANT, "Error parsing SSL Server Hello Message on FD " << fd);
            // schedule a negotiateSSl to allow openSSL parse received data
            Security::PeerConnector::NegotiateSsl(fd, this);
            return;
        }
    }
#endif
    setReadTimeout();
    Comm::SetSelect(fd, COMM_SELECT_READ, &NegotiateSsl, this, 0);
}