Security::ContextPointer
Ssl::PeekingPeerConnector::getTlsContext()
{
    return ::Config.ssl_client.sslContext;
}