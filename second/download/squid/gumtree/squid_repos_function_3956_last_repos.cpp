void
Ssl::PeekingPeerConnector::noteWantWrite()
{
    const int fd = serverConnection()->fd;
    Security::SessionPointer session(fd_table[fd].ssl);
    BIO *b = SSL_get_rbio(session.get());
    Ssl::ServerBio *srvBio = static_cast<Ssl::ServerBio *>(BIO_get_data(b));

    if ((srvBio->bumpMode() == Ssl::bumpPeek || srvBio->bumpMode() == Ssl::bumpStare) && srvBio->holdWrite()) {
        debugs(81, 3, "hold write on SSL connection on FD " << fd);
        checkForPeekAndSplice();
        return;
    }

    Security::PeerConnector::noteWantWrite();
}