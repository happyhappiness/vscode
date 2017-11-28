void
Ssl::PeerConnector::commCloseHandler(const CommCloseCbParams &params)
{
    debugs(83, 5, "FD " << params.fd << ", Ssl::PeerConnector=" << params.data);
    connectionClosed("Ssl::PeerConnector::commCloseHandler");
}