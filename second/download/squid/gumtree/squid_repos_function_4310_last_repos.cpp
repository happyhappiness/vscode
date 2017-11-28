int
ACLServerNameStrategy::match (ACLData<MatchType> * &data, ACLFilledChecklist *checklist)
{
    assert(checklist != NULL && checklist->request != NULL);

    const char *serverName = nullptr;
    SBuf clientSniKeeper; // because c_str() is not constant
    if (ConnStateData *conn = checklist->conn()) {
        const char *clientRequestedServerName = nullptr;
        clientSniKeeper = conn->tlsClientSni();
        if (clientSniKeeper.isEmpty()) {
            const char *host = checklist->request->url.host();
            if (host && *host) // paranoid first condition: host() is never nil
                clientRequestedServerName = host;
        } else
            clientRequestedServerName = clientSniKeeper.c_str();

        if (useConsensus) {
            X509 *peer_cert = conn->serverBump() ? conn->serverBump()->serverCert.get() : nullptr;
            // use the client requested name if it matches the server
            // certificate or if the certificate is not available
            if (!peer_cert || Ssl::checkX509ServerValidity(peer_cert, clientRequestedServerName))
                serverName = clientRequestedServerName;
        } else if (useClientRequested)
            serverName = clientRequestedServerName;
        else { // either no options or useServerProvided
            if (X509 *peer_cert = (conn->serverBump() ? conn->serverBump()->serverCert.get() : nullptr))
                return Ssl::matchX509CommonNames(peer_cert, (void *)data, check_cert_domain<MatchType>);
            if (!useServerProvided)
                serverName = clientRequestedServerName;
        }
    }

    if (!serverName)
        serverName = "none";

    return data->match(serverName);
}