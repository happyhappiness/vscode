apr_status_t h2_h2_init(apr_pool_t *pool, server_rec *s)
{
    (void)pool;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, "h2_h2, child_init");
    opt_ssl_engine_disable = APR_RETRIEVE_OPTIONAL_FN(ssl_engine_disable);
    opt_ssl_is_https = APR_RETRIEVE_OPTIONAL_FN(ssl_is_https);
    opt_ssl_var_lookup = APR_RETRIEVE_OPTIONAL_FN(ssl_var_lookup);
    
    if (!opt_ssl_is_https || !opt_ssl_var_lookup) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                     APLOGNO(02951) "mod_ssl does not seem to be enabled");
    }
    
    cipher_init(pool);
    
    return APR_SUCCESS;
}

int h2_h2_is_tls(conn_rec *c)
{
    return opt_ssl_is_https && opt_ssl_is_https(c);
}

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

int h2_allows_h2_direct(conn_rec *c)
{
    const h2_config *cfg = h2_config_get(c);
    int h2_direct = h2_config_geti(cfg, H2_CONF_DIRECT);
    
    if (h2_direct < 0) {
        if (h2_h2_is_tls(c)) {
            /* disabled by default on TLS */
            h2_direct = 0;
        }
        else {
            /* enabled if "Protocols h2c" is configured */
            h2_direct = ap_is_allowed_protocol(c, NULL, NULL, "h2c");
        }
    }
    return !!h2_direct;
}

int h2_allows_h2_upgrade(conn_rec *c)
{
    const h2_config *cfg = h2_config_get(c);
    int h2_upgrade = h2_config_geti(cfg, H2_CONF_UPGRADE);
    
    return h2_upgrade > 0 || (h2_upgrade < 0 && !h2_h2_is_tls(c));
}

/*******************************************************************************
 * Register various hooks
 */
static const char *const mod_reqtimeout[] = { "reqtimeout.c", NULL};
static const char* const mod_ssl[]        = {"mod_ssl.c", NULL};

void h2_h2_register_hooks(void)
{
    /* When the connection processing actually starts, we might to
     * take over, if h2* was selected as protocol.
     */
    ap_hook_process_connection(h2_h2_process_conn, 
                               mod_ssl, NULL, APR_HOOK_MIDDLE);
                               
    /* Perform connection cleanup before the actual processing happens.
     */
    ap_hook_process_connection(h2_h2_remove_timeout, 
                               mod_reqtimeout, NULL, APR_HOOK_LAST);
    
    /* With "H2SerializeHeaders On", we install the filter in this hook
