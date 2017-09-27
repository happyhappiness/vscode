apr_status_t h2_h2_init(apr_pool_t *pool, server_rec *s)
{
    (void)pool;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, "h2_h2, child_init");
    opt_ssl_engine_disable = APR_RETRIEVE_OPTIONAL_FN(ssl_engine_disable);
    opt_ssl_is_https = APR_RETRIEVE_OPTIONAL_FN(ssl_is_https);
    
    if (!opt_ssl_is_https) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                     APLOGNO(02951) "mod_ssl does not seem to be enabled");
    }
    
    return APR_SUCCESS;
}

int h2_h2_is_tls(conn_rec *c)
{
    return opt_ssl_is_https && opt_ssl_is_https(c);
}

int h2_tls_disable(conn_rec *c)
{
    if (opt_ssl_engine_disable) {
        return opt_ssl_engine_disable(c);
    }
    return 0;
}

/*******************************************************************************
 * Register various hooks
 */
static const char *const mod_reqtimeout[] = { "reqtimeout.c", NULL};

void h2_h2_register_hooks(void)
{
    /* When the connection processing actually starts, we might to
     * take over, if h2* was selected as protocol.
     */
    ap_hook_process_connection(h2_h2_process_conn, 
                               NULL, NULL, APR_HOOK_FIRST);
    /* Perform connection cleanup before the actual processing happens.
     */
    ap_hook_process_connection(h2_h2_remove_timeout, 
                               mod_reqtimeout, NULL, APR_HOOK_LAST);
    
    /* With "H2SerializeHeaders On", we install the filter in this hook
