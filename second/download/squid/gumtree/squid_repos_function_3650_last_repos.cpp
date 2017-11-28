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