http_port_list *
clone_http_port_list(http_port_list *a)
{
    http_port_list *b = new http_port_list(a->protocol);

    b->s = a->s;
    if (a->name)
        b->name = xstrdup(a->name);
    if (a->defaultsite)
        b->defaultsite = xstrdup(a->defaultsite);

    b->intercepted = a->intercepted;
    b->spoof_client_ip = a->spoof_client_ip;
    b->accel = a->accel;
    b->allow_direct = a->allow_direct;
    b->vhost = a->vhost;
    b->sslBump = a->sslBump;
    b->vport = a->vport;
    b->connection_auth_disabled = a->connection_auth_disabled;
    b->disable_pmtu_discovery = a->disable_pmtu_discovery;

    memcpy( &(b->tcp_keepalive), &(a->tcp_keepalive), sizeof(a->tcp_keepalive));

#if 0
    // AYJ: 2009-07-18: for now SSL does not clone. Configure separate ports with IPs and SSL settings

#if USE_SSL
    // XXX: temporary hack to ease move of SSL options to http_port
    http_port_list &http;

    char *cert;
    char *key;
    int version;
    char *cipher;
    char *options;
    char *clientca;
    char *cafile;
    char *capath;
    char *crlfile;
    char *dhfile;
    char *sslflags;
    char *sslContextSessionId;
    SSL_CTX *sslContext;
#endif

#endif /*0*/

    return b;
}