int h2_is_acceptable_connection(conn_rec *c, int require_all) 
{
    int is_tls = h2_h2_is_tls(c);
    const h2_config *cfg = h2_config_get(c);

    if (is_tls && h2_config_geti(cfg, H2_CONF_MODERN_TLS_ONLY) > 0) {
        /* Check TLS connection for modern TLS parameters, as defined in
         * RFC 7540 and https://wiki.mozilla.org/Security/Server_Side_TLS#Modern_compatibility
         */
        apr_pool_t *pool = c->pool;
        server_rec *s = c->base_server;
        char *val;
        
        if (!opt_ssl_var_lookup) {
            /* unable to check */
            return 0;
        }
        
        /* Need Tlsv1.2 or higher, rfc 7540, ch. 9.2
         */
        val = opt_ssl_var_lookup(pool, s, c, NULL, (char*)"SSL_PROTOCOL");
        if (val && *val) {
            if (strncmp("TLS", val, 3) 
                || !strcmp("TLSv1", val) 
                || !strcmp("TLSv1.1", val)) {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                          "h2_h2(%ld): tls protocol not suitable: %s", 
                          (long)c->id, val);
                return 0;
            }
        }
        else if (require_all) {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                          "h2_h2(%ld): tls protocol is indetermined", (long)c->id);
            return 0;
        }

        /* Check TLS cipher blacklist
         */
        val = opt_ssl_var_lookup(pool, s, c, NULL, (char*)"SSL_CIPHER");
        if (val && *val) {
            const char *source;
            if (cipher_is_blacklisted(val, &source)) {
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                              "h2_h2(%ld): tls cipher %s blacklisted by %s", 
                              (long)c->id, val, source);
                return 0;
            }
        }
        else if (require_all) {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                          "h2_h2(%ld): tls cipher is indetermined", (long)c->id);
            return 0;
        }
    }
    return 1;
}