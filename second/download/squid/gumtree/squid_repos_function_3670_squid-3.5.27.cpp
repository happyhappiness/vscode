void
ConnStateData::doPeekAndSpliceStep()
{
    SSL *ssl = fd_table[clientConnection->fd].ssl;
    BIO *b = SSL_get_rbio(ssl);
    assert(b);
    Ssl::ClientBio *bio = static_cast<Ssl::ClientBio *>(b->ptr);

    debugs(33, 5, "PeekAndSplice mode, proceed with client negotiation. Currrent state:" << SSL_state_string_long(ssl));
    bio->hold(false);

    Comm::SetSelect(clientConnection->fd, COMM_SELECT_WRITE, clientNegotiateSSL, this, 0);
    switchedToHttps_ = true;
}