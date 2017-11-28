AnyP::PortCfgPointer
AnyP::PortCfg::clone() const
{
    AnyP::PortCfgPointer b = new AnyP::PortCfg();
    b->s = s;
    if (name)
        b->name = xstrdup(name);
    if (defaultsite)
        b->defaultsite = xstrdup(defaultsite);

    b->transport = transport;
    b->flags = flags;
    b->allow_direct = allow_direct;
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