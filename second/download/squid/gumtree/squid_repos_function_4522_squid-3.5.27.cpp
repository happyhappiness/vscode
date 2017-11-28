void
Ssl::PeerConnector::checkForPeekAndSpliceMatched(const Ssl::BumpMode action)
{
    SSL *ssl = fd_table[serverConn->fd].ssl;
    BIO *b = SSL_get_rbio(ssl);
    Ssl::ServerBio *srvBio = static_cast<Ssl::ServerBio *>(b->ptr);
    debugs(83,5, "Will check for peek and splice on FD " << serverConn->fd);

    Ssl::BumpMode finalAction = action;
    Must(finalAction == Ssl::bumpSplice || finalAction == Ssl::bumpBump || finalAction == Ssl::bumpTerminate);
    // Record final decision
    if (request->clientConnectionManager.valid()) {
        request->clientConnectionManager->sslBumpMode = finalAction;
        request->clientConnectionManager->serverBump()->act.step3 = finalAction;
    }

    if (finalAction == Ssl::bumpTerminate) {
        serverConn->close();
        clientConn->close();
    } else if (finalAction != Ssl::bumpSplice) {
        //Allow write, proceed with the connection
        srvBio->holdWrite(false);
        srvBio->recordInput(false);
        Comm::SetSelect(serverConn->fd, COMM_SELECT_WRITE, &NegotiateSsl, this, 0);
        debugs(83,5, "Retry the fwdNegotiateSSL on FD " << serverConn->fd);
    } else {
        splice = true;
        // Ssl Negotiation stops here. Last SSL checks for valid certificates
        // and if done, switch to tunnel mode
        if (sslFinalized())
            switchToTunnel(request.getRaw(), clientConn, serverConn);
    }
}