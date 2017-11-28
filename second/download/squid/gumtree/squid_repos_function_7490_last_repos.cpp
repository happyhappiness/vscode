Security::ContextPointer
Security::BlindPeerConnector::getTlsContext()
{
    if (const CachePeer *peer = serverConnection()->getPeer()) {
        assert(peer->secure.encryptTransport);
        return peer->sslContext;
    }
    return ::Config.ssl_client.sslContext;
}