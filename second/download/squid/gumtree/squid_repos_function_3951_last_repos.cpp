void
Ssl::PeekingPeerConnector::checkForPeekAndSpliceMatched(const Ssl::BumpMode action)
{
    Security::SessionPointer session(fd_table[serverConn->fd].ssl);
    BIO *b = SSL_get_rbio(session.get());
    Ssl::ServerBio *srvBio = static_cast<Ssl::ServerBio *>(BIO_get_data(b));
    debugs(83,5, "Will check for peek and splice on FD " << serverConn->fd);

    Ssl::BumpMode finalAction = action;
    Must(finalAction == Ssl::bumpSplice || finalAction == Ssl::bumpBump || finalAction == Ssl::bumpTerminate);
    // Record final decision
    if (request->clientConnectionManager.valid()) {
        request->clientConnectionManager->sslBumpMode = finalAction;
        request->clientConnectionManager->serverBump()->act.step3 = finalAction;
    }
    al->ssl.bumpMode = finalAction;

    if (finalAction == Ssl::bumpTerminate) {
        serverConn->close();
        clientConn->close();
    } else if (finalAction != Ssl::bumpSplice) {
        //Allow write, proceed with the connection
        srvBio->holdWrite(false);
        srvBio->recordInput(false);
        debugs(83,5, "Retry the fwdNegotiateSSL on FD " << serverConn->fd);
        Security::PeerConnector::noteWantWrite();
    } else {
        splice = true;
        // Ssl Negotiation stops here. Last SSL checks for valid certificates
        // and if done, switch to tunnel mode
        if (sslFinalized()) {
            debugs(83,5, "Abort NegotiateSSL on FD " << serverConn->fd << " and splice the connection");
            callBack();
        }
    }
}