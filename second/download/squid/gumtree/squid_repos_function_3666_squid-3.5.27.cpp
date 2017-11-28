static void
clientPeekAndSpliceSSL(int fd, void *data)
{
    ConnStateData *conn = (ConnStateData *)data;
    SSL *ssl = fd_table[fd].ssl;

    debugs(83, 5, "Start peek and splice on FD " << fd);

    if (!Squid_SSL_accept(conn, clientPeekAndSpliceSSL))
        debugs(83, 2, "SSL_accept failed.");

    BIO *b = SSL_get_rbio(ssl);
    assert(b);
    Ssl::ClientBio *bio = static_cast<Ssl::ClientBio *>(b->ptr);
    if (bio->gotHello()) {
        if (conn->serverBump()) {
            Ssl::Bio::sslFeatures const &features = bio->getFeatures();
            if (!features.serverName.isEmpty()) {
                conn->serverBump()->clientSni = features.serverName;
                conn->resetSslCommonName(features.serverName.c_str());
            }
        }

        debugs(83, 5, "I got hello. Start forwarding the request!!! ");
        Comm::SetSelect(fd, COMM_SELECT_READ, NULL, NULL, 0);
        Comm::SetSelect(fd, COMM_SELECT_WRITE, NULL, NULL, 0);
        conn->startPeekAndSpliceDone();
        return;
    }
}