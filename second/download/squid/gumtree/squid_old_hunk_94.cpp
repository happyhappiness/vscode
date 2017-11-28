    } else if (strcmp(token, "generate-host-certificates=on") == 0) {
        s->generateHostCertificates = true;
    } else if (strcmp(token, "generate-host-certificates=off") == 0) {
        s->generateHostCertificates = false;
    } else if (strncmp(token, "dynamic_cert_mem_cache_size=", 28) == 0) {
        parseBytesOptionValue(&s->dynamicCertMemCacheSize, B_BYTES_STR, token + 28);
    } else if (strcasecmp(token, "sslBump") == 0) {
        debugs(3, DBG_CRITICAL, "WARNING: '" << token << "' is deprecated " <<
               "in http_port. Use 'ssl-bump' instead.");
        s->sslBump = 1; // accelerated when bumped, otherwise not
    } else if (strcmp(token, "ssl-bump") == 0) {
        s->sslBump = 1; // accelerated when bumped, otherwise not
#endif
    } else {
        self_destruct();
    }

    if ( s->spoof_client_ip && (s->intercepted || s->accel) ) {
        debugs(3,DBG_CRITICAL, "http(s)_port: TPROXY option requires its own interception port. It cannot be shared.");
        self_destruct();
    }
}

static http_port_list *
create_http_port(char *portspec)
{
    http_port_list *s = new http_port_list("http");
    parse_http_port_specification(s, portspec);
    return s;
}

void
add_http_port(char *portspec)
{
    http_port_list *s = create_http_port(portspec);
    // we may need to merge better of the above returns a list with clones
    assert(s->next == NULL);
    s->next = cbdataReference(Config.Sockaddr.http);
    cbdataReferenceDone(Config.Sockaddr.http);
    Config.Sockaddr.http = cbdataReference(s);
}

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

static void
parse_http_port_list(http_port_list ** head)
{
    char *token = strtok(NULL, w_space);

    if (!token) {
        self_destruct();
        return;
    }

    http_port_list *s = create_http_port(token);

    /* parse options ... */
    while ((token = strtok(NULL, w_space))) {
        parse_http_port_option(s, token);
    }

    if (Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK && s->s.IsAnyAddr()) {
        // clone the port options from *s to *(s->next)
        s->next = cbdataReference(clone_http_port_list(s));
        s->next->s.SetIPv4();
        debugs(3, 3, "http(s)_port: clone wildcard address for split-stack: " << s->s << " and " << s->next->s);
    }

    while (*head)
        head = &(*head)->next;

    *head = cbdataReference(s);
}

static void
dump_generic_http_port(StoreEntry * e, const char *n, const http_port_list * s)
{
    char buf[MAX_IPSTRLEN];

    storeAppendPrintf(e, "%s %s",
                      n,
                      s->s.ToURL(buf,MAX_IPSTRLEN));
