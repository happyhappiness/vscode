 * invocation, for now at least.
 */
static int h2_post_config(apr_pool_t *p, apr_pool_t *plog,
                          apr_pool_t *ptemp, server_rec *s)
{
    void *data = NULL;
    const char *mod_h2_init_key = "mod_h2_init_counter";
    nghttp2_info *ngh2;
    apr_status_t status;
    (void)plog;(void)ptemp;
    
    apr_pool_userdata_get(&data, mod_h2_init_key, s->process->pool);
    if ( data == NULL ) {
        ap_log_error( APLOG_MARK, APLOG_DEBUG, 0, s,
                     "initializing post config dry run");
        apr_pool_userdata_set((const void *)1, mod_h2_init_key,
                              apr_pool_cleanup_null, s->process->pool);
        return APR_SUCCESS;
    }
    
    ngh2 = nghttp2_version(0);
    ap_log_error( APLOG_MARK, APLOG_INFO, 0, s,
                 "mod_http2 (v%s, nghttp2 %s), initializing...",
                 MOD_HTTP2_VERSION, ngh2? ngh2->version_str : "unknown");
    
    switch (h2_conn_mpm_type()) {
        case H2_MPM_EVENT:
        case H2_MPM_WORKER:
            /* all fine, we know these ones */
            break;
        case H2_MPM_PREFORK:
            /* ok, we now know how to handle that one */
            break;
        case H2_MPM_UNKNOWN:
            /* ??? */
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "post_config: mpm type unknown");
            break;
    }
    
    status = h2_h2_init(p, s);
    if (status == APR_SUCCESS) {
        status = h2_switch_init(p, s);
    }
    
    return status;
}

/* Runs once per created child process. Perform any process 
 * related initionalization here.
 */
static void h2_child_init(apr_pool_t *pool, server_rec *s)
{
    /* Set up our connection processing */
    apr_status_t status = h2_conn_child_init(pool, s);
    if (status != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, status, s,
                     APLOGNO(02949) "initializing connection handling");
    }
}

/* Install this module into the apache2 infrastructure.
 */
static void h2_hooks(apr_pool_t *pool)
{
    static const char *const mod_ssl[] = { "mod_ssl.c", NULL};
    
    ap_log_perror(APLOG_MARK, APLOG_INFO, 0, pool, "installing hooks");
    
    /* Run once after configuration is set, but before mpm children initialize.
     */
    ap_hook_post_config(h2_post_config, mod_ssl, NULL, APR_HOOK_MIDDLE);
    
    /* Run once after a child process has been created.
