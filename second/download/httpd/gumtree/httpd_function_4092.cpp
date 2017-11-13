static int remoteip_modify_connection(request_rec *r)
{
    conn_rec *c = r->connection;
    remoteip_config_t *config = (remoteip_config_t *)
        ap_get_module_config(r->server->module_config, &remoteip_module);
    remoteip_conn_t *conn;
#ifdef REMOTEIP_OPTIMIZED
    apr_sockaddr_t temp_sa_buff;
    apr_sockaddr_t *temp_sa = &temp_sa_buff;
#else
    apr_sockaddr_t *temp_sa;
#endif
    apr_status_t rv;
    char *remote = (char *) apr_table_get(r->headers_in, config->header_name);
    char *proxy_ips = NULL;
    char *parse_remote;
    char *eos;
    unsigned char *addrbyte;
    void *internal = NULL;

    apr_pool_userdata_get((void*)&conn, "mod_remoteip-conn", c->pool);

    if (conn) {
        if (remote && (strcmp(remote, conn->prior_remote) == 0)) {
            /* TODO: Recycle r-> overrides from previous request
             */
            goto ditto_request_rec;
        }
        else {
            /* TODO: Revert connection from previous request
             */
            c->remote_addr = conn->orig_addr;
            c->remote_ip = (char *) conn->orig_ip;
        }
    }

    if (!remote)
        return OK;

    remote = apr_pstrdup(r->pool, remote);

#ifdef REMOTEIP_OPTIMIZED
    memcpy(&temp_sa, c->remote_addr, sizeof(temp_sa));
    temp_sa->pool = r->pool;
#else
    temp_sa = c->remote_addr;
#endif

    while (remote) {

        /* verify c->remote_addr is trusted if there is a trusted proxy list
         */
        if (config->proxymatch_ip) {
            int i;
            remoteip_proxymatch_t *match;
            match = (remoteip_proxymatch_t *)config->proxymatch_ip->elts;
            for (i = 0; i < config->proxymatch_ip->nelts; ++i) {
                if (apr_ipsubnet_test(match[i].ip, c->remote_addr)) {
                    internal = match[i].internal;
                    break;
                }
            }
            if (i && i >= config->proxymatch_ip->nelts)
                break;
        }

        if ((parse_remote = strrchr(remote, ',')) == NULL) {
            parse_remote = remote;
            remote = NULL;
        }
        else {
            *(parse_remote++) = '\0';
        }

        while (*parse_remote == ' ') 
            ++parse_remote;

        eos = parse_remote + strlen(parse_remote) - 1;
        while (eos >= parse_remote && *eos == ' ')
            *(eos--) = '\0';

        if (eos < parse_remote) {
            if (remote)
                *(remote + strlen(remote)) = ',';
            else
                remote = parse_remote;
            break;
        }

#ifdef REMOTEIP_OPTIMIZED
        /* Decode remote_addr - sucks; apr_sockaddr_vars_set isn't 'public' */
        if (inet_pton(AF_INET, parse_remote, 
                      &temp_sa_buff->sa.sin.sin_addr) > 0) {
            apr_sockaddr_vars_set(temp_sa, APR_INET, temp_sa.port);
        }
#if APR_HAVE_IPV6
        else if (inet_pton(AF_INET6, parse_remote, 
                           &temp_sa->sa.sin6.sin6_addr) > 0) {
            apr_sockaddr_vars_set(temp_sa, APR_INET6, temp_sa.port);
        }
#endif
        else {
            rv = apr_get_netos_error();
#else /* !REMOTEIP_OPTIMIZED */
        /* We map as IPv4 rather than IPv6 for equivilant host names
         * or IPV4OVERIPV6 
         */
        rv = apr_sockaddr_info_get(&temp_sa,  parse_remote, 
                                   APR_UNSPEC, temp_sa->port,
                                   APR_IPV4_ADDR_OK, r->pool);
        if (rv != APR_SUCCESS) {
#endif
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG,  rv, r,
                          "RemoteIP: Header %s value of %s cannot be parsed "
                          "as a client IP",
                          config->header_name, parse_remote);
            if (remote)
                *(remote + strlen(remote)) = ',';
            else
                remote = parse_remote;
            break;
        }

        addrbyte = (unsigned char *) &temp_sa->sa.sin.sin_addr;

        /* For intranet (Internal proxies) ignore all restrictions below */
        if (!internal
              && ((temp_sa->family == APR_INET
                   /* For internet (non-Internal proxies) deny all
                    * RFC3330 designated local/private subnets:
                    * 10.0.0.0/8   169.254.0.0/16  192.168.0.0/16 
                    * 127.0.0.0/8  172.16.0.0/12
                    */
                      && (addrbyte[0] == 10
                       || addrbyte[0] == 127
                       || (addrbyte[0] == 169 && addrbyte[1] == 254)
                       || (addrbyte[0] == 172 && (addrbyte[1] & 0xf0) == 16)
                       || (addrbyte[0] == 192 && addrbyte[1] == 168)))
#if APR_HAVE_IPV6
               || (temp_sa->family == APR_INET6
                   /* For internet (non-Internal proxies) we translated 
                    * IPv4-over-IPv6-mapped addresses as IPv4, above.
                    * Accept only Global Unicast 2000::/3 defined by RFC4291
                    */
                      && ((temp_sa->sa.sin6.sin6_addr.s6_addr[0] & 0xe0) != 0x20))
#endif
        )) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG,  rv, r,
                          "RemoteIP: Header %s value of %s appears to be "
                          "a private IP or nonsensical.  Ignored",
                          config->header_name, parse_remote);
            if (remote)
                *(remote + strlen(remote)) = ',';
            else
                remote = parse_remote;
            break;
        }

        if (!conn) {
            conn = (remoteip_conn_t *) apr_palloc(c->pool, sizeof(*conn));
            apr_pool_userdata_set(conn, "mod_remoteip-conn", NULL, c->pool);
            conn->orig_addr = c->remote_addr;
            conn->orig_ip = c->remote_ip;
        }

        /* Set remote_ip string */
        if (!internal) {
            if (proxy_ips)
                proxy_ips = apr_pstrcat(r->pool, proxy_ips, ", ", 
                                        c->remote_ip, NULL);
            else
                proxy_ips = c->remote_ip;
        }

        c->remote_addr = temp_sa;
        apr_sockaddr_ip_get(&c->remote_ip, c->remote_addr);
    }

    /* Nothing happened? */
    if (!conn || (c->remote_addr == conn->orig_addr))
        return OK;

    /* Fixups here, remote becomes the new Via header value, etc 
     * In the heavy operations above we used request scope, to limit
     * conn pool memory growth on keepalives, so here we must scope
     * the final results to the connection pool lifetime.
     * To limit memory growth, we keep recycling the same buffer
     * for the final apr_sockaddr_t in the remoteip conn rec.
     */
    c->remote_ip = apr_pstrdup(c->pool, c->remote_ip);
    conn->proxied_ip = c->remote_ip;
    memcpy(&conn->proxied_addr, &temp_sa, sizeof(temp_sa));
    conn->proxied_addr.pool = c->pool;
    c->remote_addr = &conn->proxied_addr;

    if (remote)
        remote = apr_pstrdup(c->pool, remote);
    conn->proxied_remote = remote;
    conn->prior_remote = apr_pstrdup(c->pool, apr_table_get(r->headers_in, 
                                                      config->header_name));
    if (proxy_ips)
        proxy_ips = apr_pstrdup(c->pool, proxy_ips);
    conn->proxy_ips = proxy_ips;

    /* Unset remote_host string DNS lookups */
    c->remote_host = NULL;
    c->remote_logname = NULL;

ditto_request_rec:
    if (conn->proxied_remote)
        apr_table_setn(r->headers_in, config->header_name,
                       conn->proxied_remote);
    else
        apr_table_unset(r->headers_in, config->header_name);
    if (conn->proxy_ips) {
        apr_table_setn(r->notes, "remoteip-proxy-ip-list", conn->proxy_ips);
        if (config->proxies_header_name)
            apr_table_setn(r->headers_in, config->proxies_header_name,
                           conn->proxy_ips);
    }

    ap_log_rerror(APLOG_MARK, APLOG_INFO|APLOG_NOERRNO, 0, r,
                  conn->proxy_ips 
                      ? "Using %s as client's IP by proxies %s"
                      : "Using %s as client's IP by internal proxies",
                  conn->proxied_ip, conn->proxy_ips);
    return OK;
}

static const command_rec remoteip_cmds[] =
{
    AP_INIT_TAKE1("RemoteIPHeader", header_name_set, NULL, RSRC_CONF,
                  "Specifies a request header to trust as the client IP, "
                  "e.g. X-Forwarded-For"),
    AP_INIT_TAKE1("RemoteIPProxiesHeader", proxies_header_name_set,
                  NULL, RSRC_CONF,
                  "Specifies a request header to record proxy IP's, "
                  "e.g. X-Forwarded-By; if not given then do not record"),
    AP_INIT_ITERATE("RemoteIPTrustedProxy", proxies_set, 0, RSRC_CONF,
                    "Specifies one or more proxies which are trusted "
                    "to present IP headers"),
    AP_INIT_ITERATE("RemoteIPInternalProxy", proxies_set, (void*)1, RSRC_CONF,
                    "Specifies one or more internal (transparent) proxies "
                    "which are trusted to present IP headers"),
    AP_INIT_TAKE1("RemoteIPTrustedProxyList", proxylist_read, 0,
                  RSRC_CONF | EXEC_ON_READ,
                  "The filename to read the list of trusted proxies, "
                  "see the RemoteIPTrustedProxy directive"),
    AP_INIT_TAKE1("RemoteIPInternalProxyList", proxylist_read, (void*)1,
                  RSRC_CONF | EXEC_ON_READ,
                  "The filename to read the list of internal proxies, "
                  "see the RemoteIPInternalProxy directive"),
    { NULL }
};

static void register_hooks(apr_pool_t *p)
{
    ap_hook_post_read_request(remoteip_modify_connection, NULL, NULL, APR_HOOK_FIRST);
}

AP_DECLARE_MODULE(remoteip) = {
    STANDARD20_MODULE_STUFF,
    NULL,                          /* create per-directory config structure */
    NULL,                          /* merge per-directory config structures */
    create_remoteip_server_config, /* create per-server config structure */
    merge_remoteip_server_config,  /* merge per-server config structures */
    remoteip_cmds,                 /* command apr_table_t */
    register_hooks                 /* register hooks */
}