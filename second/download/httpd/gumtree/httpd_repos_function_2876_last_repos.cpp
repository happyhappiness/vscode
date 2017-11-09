static int h2_proxy_post_config(apr_pool_t *p, apr_pool_t *plog,
                                apr_pool_t *ptemp, server_rec *s)
{
    void *data = NULL;
    const char *init_key = "mod_proxy_http2_init_counter";
    nghttp2_info *ngh2;
    apr_status_t status = APR_SUCCESS;
    (void)plog;(void)ptemp;
    
    apr_pool_userdata_get(&data, init_key, s->process->pool);
    if ( data == NULL ) {
        apr_pool_userdata_set((const void *)1, init_key,
                              apr_pool_cleanup_null, s->process->pool);
        return APR_SUCCESS;
    }
    
    ngh2 = nghttp2_version(0);
    ap_log_error( APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(03349)
                 "mod_proxy_http2 (v%s, nghttp2 %s), initializing...",
                 MOD_HTTP2_VERSION, ngh2? ngh2->version_str : "unknown");
    
    is_h2 = APR_RETRIEVE_OPTIONAL_FN(http2_is_h2);
    req_engine_push = APR_RETRIEVE_OPTIONAL_FN(http2_req_engine_push);
    req_engine_pull = APR_RETRIEVE_OPTIONAL_FN(http2_req_engine_pull);
    req_engine_done = APR_RETRIEVE_OPTIONAL_FN(http2_req_engine_done);
    
    /* we need all of them */
    if (!req_engine_push || !req_engine_pull || !req_engine_done) {
        req_engine_push = NULL;
        req_engine_pull = NULL;
        req_engine_done = NULL;
    }
    
    return status;
}