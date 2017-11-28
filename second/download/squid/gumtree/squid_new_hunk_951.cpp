    }
}

void Adaptation::Icap::Xaction::fillDoneStatus(MemBuf &buf) const
{
    if (haveConnection() && commEof)
        buf.appendf("Comm(%d)", connection->fd);

    if (stopReason != NULL)
        buf.append("Stopped", 7);
}

bool Adaptation::Icap::Xaction::fillVirginHttpHeader(MemBuf &) const
{
    return false;
}

bool
Ssl::IcapPeerConnector::initialize(Security::SessionPointer &serverSession)
{
    if (!Security::PeerConnector::initialize(serverSession))
        return false;

    assert(!icapService->cfg().secure.sslDomain.isEmpty());
#if USE_OPENSSL
    SBuf *host = new SBuf(icapService->cfg().secure.sslDomain);
    SSL_set_ex_data(serverSession.get(), ssl_ex_index_server, host);

    ACLFilledChecklist *check = static_cast<ACLFilledChecklist *>(SSL_get_ex_data(serverSession.get(), ssl_ex_index_cert_error_check));
    if (check)
        check->dst_peer_name = *host;
#endif

    Security::SetSessionResumeData(serverSession, icapService->sslSession);
    return true;
}

void
Ssl::IcapPeerConnector::noteNegotiationDone(ErrorState *error)
{
    if (error)
        return;

    const int fd = serverConnection()->fd;
    Security::MaybeGetSessionResumeData(fd_table[fd].ssl, icapService->sslSession);
}

void
Adaptation::Icap::Xaction::handleSecuredPeer(Security::EncryptorAnswer &answer)
{
    Must(securer != NULL);
    securer = NULL;

    if (closer != NULL) {
        if (answer.conn != NULL)
            comm_remove_close_handler(answer.conn->fd, closer);
        else
            closer->cancel("securing completed");
        closer = NULL;
    }

    if (answer.error.get()) {
        if (answer.conn != NULL)
            answer.conn->close();
        debugs(93, 2, typeName <<
               " TLS negotiation to " << service().cfg().uri << " failed");
        service().noteConnectionFailed("failure");
        detailError(ERR_DETAIL_ICAP_XACT_SSL_START);
        throw TexcHere("cannot connect to the TLS ICAP service");
    }

    debugs(93, 5, "TLS negotiation to " << service().cfg().uri << " complete");

    service().noteConnectionUse(answer.conn);

    handleCommConnected();
}

