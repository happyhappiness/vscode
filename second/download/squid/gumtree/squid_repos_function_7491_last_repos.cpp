bool
Security::BlindPeerConnector::initialize(Security::SessionPointer &serverSession)
{
    if (!Security::PeerConnector::initialize(serverSession)) {
        debugs(83, 5, "Security::PeerConnector::initialize failed");
        return false;
    }

    if (const CachePeer *peer = serverConnection()->getPeer()) {
        assert(peer);

        // NP: domain may be a raw-IP but it is now always set
        assert(!peer->secure.sslDomain.isEmpty());

#if USE_OPENSSL
        // const loss is okay here, ssl_ex_index_server is only read and not assigned a destructor
        SBuf *host = new SBuf(peer->secure.sslDomain);
        SSL_set_ex_data(serverSession.get(), ssl_ex_index_server, host);

        Security::SetSessionResumeData(serverSession, peer->sslSession);
    } else {
        SBuf *hostName = new SBuf(request->url.host());
        SSL_set_ex_data(serverSession.get(), ssl_ex_index_server, (void*)hostName);
#endif
    }

    debugs(83, 5, "success");
    return true;
}