     * just the certificate/keys of one virtual host (which one cannot be said
     * easily - but that doesn't matter here).
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
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0,
                         base_server,
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
