static int proxy_http_post_config(apr_pool_t *pconf, apr_pool_t *plog,
        apr_pool_t *ptemp, server_rec *s)
{

    /* proxy_http_post_config() will be called twice during startup.  So, don't
     * set up the static data the 1st time through. */
    if (ap_state_query(AP_SQ_MAIN_STATE) == AP_SQ_MS_CREATE_PRE_CONFIG) {
        return OK;
    }

    if (!ap_proxy_clear_connection_fn) {
        ap_proxy_clear_connection_fn =
                APR_RETRIEVE_OPTIONAL_FN(ap_proxy_clear_connection);
        if (!ap_proxy_clear_connection_fn) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02477)
                         "mod_proxy must be loaded for mod_proxy_http");
            return !OK;
        }
    }

    return OK;
}