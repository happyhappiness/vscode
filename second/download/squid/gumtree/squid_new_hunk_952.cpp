    b->vhost = vhost;
    b->vport = vport;
    b->connection_auth_disabled = connection_auth_disabled;
    b->ftp_track_dirs = ftp_track_dirs;
    b->disable_pmtu_discovery = disable_pmtu_discovery;
    b->tcp_keepalive = tcp_keepalive;
    b->secure = secure;

#if USE_OPENSSL
    if (clientca)
        b->clientca = xstrdup(clientca);
    if (sslContextSessionId)
        b->sslContextSessionId = xstrdup(sslContextSessionId);

#if 0
    // TODO: AYJ: 2015-01-15: for now SSL does not clone the context object.
    // cloning should only be done before the PortCfg is post-configure initialized and opened
    Security::ContextPointer sslContext;
#endif

#endif /*0*/

    return b;
}

#if USE_OPENSSL
void
AnyP::PortCfg::configureSslServerContext()
{
    if (!secure.certs.empty()) {
        Security::KeyData &keys = secure.certs.front();
        Ssl::readCertChainAndPrivateKeyFromFiles(signingCert, signPkey, certsToChain, keys.certFile.c_str(), keys.privateKeyFile.c_str());
    }

    if (!signingCert) {
        char buf[128];
        fatalf("No valid signing SSL certificate configured for %s_port %s", AnyP::ProtocolType_str[transport.protocol],  s.toUrl(buf, sizeof(buf)));
    }

