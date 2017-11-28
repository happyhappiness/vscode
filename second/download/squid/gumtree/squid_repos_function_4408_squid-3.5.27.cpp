bool
Ssl::ServerBio::resumingSession()
{
    if (!serverFeatures.initialized_)
        serverFeatures.get(rbuf, false);

    if (!clientFeatures.sessionId.isEmpty() && !serverFeatures.sessionId.isEmpty())
        return clientFeatures.sessionId == serverFeatures.sessionId;

    // is this a session resuming attempt using TLS tickets?
    if (clientFeatures.hasTlsTicket && serverFeatures.hasCcsOrNst)
        return true;

    return false;
}