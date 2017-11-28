void
Ssl::PeekingPeerConnector::noteNegotiationError(const int result, const int ssl_error, const int ssl_lib_error)
{
    const int fd = serverConnection()->fd;
    Security::SessionPointer session(fd_table[fd].ssl);
    BIO *b = SSL_get_rbio(session.get());
    Ssl::ServerBio *srvBio = static_cast<Ssl::ServerBio *>(BIO_get_data(b));

    // In Peek mode, the ClientHello message sent to the server. If the
    // server resuming a previous (spliced) SSL session with the client,
    // then probably we are here because local SSL object does not know
    // anything about the session being resumed.
    //
    if (srvBio->bumpMode() == Ssl::bumpPeek && (resumingSession = srvBio->resumingSession())) {
        // we currently splice all resumed sessions unconditionally
        if (const bool spliceResumed = true) {
            bypassCertValidator();
            checkForPeekAndSpliceMatched(Ssl::bumpSplice);
            return;
        } // else fall through to find a matching ssl_bump action (with limited info)
    }

    // If we are in peek-and-splice mode and still we did not write to
    // server yet, try to see if we should splice.
    // In this case the connection can be saved.
    // If the checklist decision is do not splice a new error will
    // occur in the next SSL_connect call, and we will fail again.
    // Abort on certificate validation errors to avoid splicing and
    // thus hiding them.
    // Abort if no certificate found probably because of malformed or
    // unsupported server Hello message (TODO: make configurable).
    if (!SSL_get_ex_data(session.get(), ssl_ex_index_ssl_error_detail) &&
            (srvBio->bumpMode() == Ssl::bumpPeek  || srvBio->bumpMode() == Ssl::bumpStare) && srvBio->holdWrite()) {
        Security::CertPointer serverCert(SSL_get_peer_certificate(session.get()));
        if (serverCert) {
            debugs(81, 3, "Error ("  << Security::ErrorString(ssl_lib_error) <<  ") but, hold write on SSL connection on FD " << fd);
            checkForPeekAndSplice();
            return;
        }
    }

    // else call parent noteNegotiationError to produce an error page
    Security::PeerConnector::noteNegotiationError(result, ssl_error, ssl_lib_error);
}