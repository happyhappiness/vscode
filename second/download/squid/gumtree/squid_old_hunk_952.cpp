    b->vhost = vhost;
    b->vport = vport;
    b->connection_auth_disabled = connection_auth_disabled;
    b->ftp_track_dirs = ftp_track_dirs;
    b->disable_pmtu_discovery = disable_pmtu_discovery;
    b->tcp_keepalive = tcp_keepalive;

#if USE_OPENSSL
    if (cert)
        b->cert = xstrdup(cert);
    if (key)
        b->key = xstrdup(key);
    b->version = version;
    if (cipher)
        b->cipher = xstrdup(cipher);
    if (options)
        b->options = xstrdup(options);
    if (clientca)
        b->clientca = xstrdup(clientca);
    if (cafile)
        b->cafile = xstrdup(cafile);
    if (capath)
        b->capath = xstrdup(capath);
    if (crlfile)
        b->crlfile = xstrdup(crlfile);
    if (dhfile)
        b->dhfile = xstrdup(dhfile);
    if (tls_dh)
        b->tls_dh = xstrdup(tls_dh);
    if (sslflags)
        b->sslflags = xstrdup(sslflags);
    if (sslContextSessionId)
        b->sslContextSessionId = xstrdup(sslContextSessionId);

#if 0
    // TODO: AYJ: 2015-01-15: for now SSL does not clone the context object.
    // cloning should only be done before the PortCfg is post-configure initialized and opened
    SSL_CTX *sslContext;
#endif

#endif /*0*/

    return b;
}

#if USE_OPENSSL
void
AnyP::PortCfg::configureSslServerContext()
{
    if (cert)
        Ssl::readCertChainAndPrivateKeyFromFiles(signingCert, signPkey, certsToChain, cert, key);

    if (!signingCert) {
        char buf[128];
        fatalf("No valid signing SSL certificate configured for %s_port %s", AnyP::ProtocolType_str[transport.protocol],  s.toUrl(buf, sizeof(buf)));
    }

