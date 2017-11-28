void
Ssl::PeerConnector::checkForPeekAndSplice()
{
    // Mark Step3 of bumping
    if (request->clientConnectionManager.valid()) {
        if (Ssl::ServerBump *serverBump = request->clientConnectionManager->serverBump()) {
            serverBump->step = Ssl::bumpStep3;
        }
    }

    handleServerCertificate();

    ACLFilledChecklist *acl_checklist = new ACLFilledChecklist(
        ::Config.accessList.ssl_bump,
        request.getRaw(), NULL);
    acl_checklist->banAction(allow_t(ACCESS_ALLOWED, Ssl::bumpNone));
    acl_checklist->banAction(allow_t(ACCESS_ALLOWED, Ssl::bumpPeek));
    acl_checklist->banAction(allow_t(ACCESS_ALLOWED, Ssl::bumpStare));
    acl_checklist->banAction(allow_t(ACCESS_ALLOWED, Ssl::bumpClientFirst));
    acl_checklist->banAction(allow_t(ACCESS_ALLOWED, Ssl::bumpServerFirst));
    SSL *ssl = fd_table[serverConn->fd].ssl;
    BIO *b = SSL_get_rbio(ssl);
    Ssl::ServerBio *srvBio = static_cast<Ssl::ServerBio *>(b->ptr);
    if (!srvBio->canSplice())
        acl_checklist->banAction(allow_t(ACCESS_ALLOWED, Ssl::bumpSplice));
    if (!srvBio->canBump())
        acl_checklist->banAction(allow_t(ACCESS_ALLOWED, Ssl::bumpBump));
    acl_checklist->nonBlockingCheck(Ssl::PeerConnector::cbCheckForPeekAndSpliceDone, this);
}