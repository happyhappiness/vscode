void
Ssl::PeerConnector::connectionClosed(const char *reason)
{
    mustStop(reason);
    callback = NULL;
}