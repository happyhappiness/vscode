apr_status_t ssl_init_CheckServers(server_rec *base_server, apr_pool_t *p)
{
    server_rec *s;
    SSLSrvConfigRec *sc;
#ifndef HAVE_TLSEXT
    server_rec *ps;
    apr_hash_t *table;
    const char *key;
    apr_ssize_t klen;

    BOOL conflict = FALSE;
#endif

    /*
     * Give out warnings when a server has HTTPS configured
     * for the HTTP port or vice versa
     */
    for (s = base_server; s; s = s->next) {
        sc = mySrvConfig(s);

        if ((sc->enabled == SSL_ENABLED_TRUE) && (s->port == DEFAULT_HTTP_PORT)) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0,
                         base_server, APLOGNO(01915)
                         "Init: (%s) You configured HTTPS(%d) "
                         "on the standard HTTP(%d) port!",
                         ssl_util_vhostid(p, s),
                         DEFAULT_HTTPS_PORT, DEFAULT_HTTP_PORT);
        }

        if ((sc->enabled == SSL_ENABLED_FALSE) && (s->port == DEFAULT_HTTPS_PORT)) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0,
                         base_server, APLOGNO(01916)
                         "Init: (%s) You configured HTTP(%d) "
                         "on the standard HTTPS(%d) port!",
                         ssl_util_vhostid(p, s),
                         DEFAULT_HTTP_PORT, DEFAULT_HTTPS_PORT);
        }
    }

#ifndef HAVE_TLSEXT
    /*
     * Give out warnings when more than one SSL-aware virtual server uses the
     * same IP:port and an OpenSSL version without support for TLS extensions
     * (SNI in particular) is used.
     */
    table = apr_hash_make(p);

    for (s = base_server; s; s = s->next) {
        char *addr;

        sc = mySrvConfig(s);

        if (!((sc->enabled == SSL_ENABLED_TRUE) && s->addrs)) {
            continue;
        }

        apr_sockaddr_ip_get(&addr, s->addrs->host_addr);
        key = apr_psprintf(p, "%s:%u", addr, s->addrs->host_port);
        klen = strlen(key);

        if ((ps = (server_rec *)apr_hash_get(table, key, klen))) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, base_server, APLOGNO(02662)
                         "Init: SSL server IP/port conflict: "
                         "%s (%s:%d) vs. %s (%s:%d)",
                         ssl_util_vhostid(p, s),
                         (s->defn_name ? s->defn_name : "unknown"),
                         s->defn_line_number,
                         ssl_util_vhostid(p, ps),
                         (ps->defn_name ? ps->defn_name : "unknown"),
                         ps->defn_line_number);
            conflict = TRUE;
            continue;
        }

        apr_hash_set(table, key, klen, s);
    }

    if (conflict) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, base_server, APLOGNO(01917)
                     "Init: Name-based SSL virtual hosts require "
                     "an OpenSSL version with support for TLS extensions "
                     "(RFC 6066 - Server Name Indication / SNI), "
                     "but the currently used library version (%s) is "
                     "lacking this feature", SSLeay_version(SSLEAY_VERSION));
    }
#endif

    return APR_SUCCESS;
}