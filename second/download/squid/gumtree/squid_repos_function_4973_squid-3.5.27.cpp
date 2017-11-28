int
ACLServerNameStrategy::match (ACLData<MatchType> * &data, ACLFilledChecklist *checklist, ACLFlags &flags)
{
    assert(checklist != NULL && checklist->request != NULL);

    const char *serverName = NULL;
    SBuf serverNameKeeper; // because c_str() is not constant
    if (ConnStateData *conn = checklist->conn()) {
        if (conn->serverBump()) {
            if (X509 *peer_cert = conn->serverBump()->serverCert.get())
                return Ssl::matchX509CommonNames(peer_cert, (void *)data, check_cert_domain<MatchType>);
        }

        if (conn->sslCommonName().isEmpty()) {
            const char *host = checklist->request->GetHost();
            if (host && *host) // paranoid first condition: host() is never nil
                serverName = host;
        } else {
            serverNameKeeper = conn->sslCommonName();
            serverName = serverNameKeeper.c_str();
        }
    }

    if (!serverName)
        serverName = "none";

    return data->match(serverName);
}