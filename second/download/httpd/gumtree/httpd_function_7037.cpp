static int h2_post_config(apr_pool_t *p, apr_pool_t *plog,
                          apr_pool_t *ptemp, server_rec *s)
{
    void *data = NULL;
    const char *mod_h2_init_key = "mod_http2_init_counter";
    nghttp2_info *ngh2;
    apr_status_t status;
    
    (void)plog;(void)ptemp;
#ifdef H2_NG2_CHANGE_PRIO
    myfeats.change_prio = 1;
#endif
#ifdef H2_OPENSSL
    myfeats.sha256 = 1;
#endif
#ifdef H2_NG2_INVALID_HEADER_CB
    myfeats.inv_headers = 1;
#endif
#ifdef H2_NG2_LOCAL_WIN_SIZE
    myfeats.dyn_windows = 1;
#endif
    
    apr_pool_userdata_get(&data, mod_h2_init_key, s->process->pool);
    if ( data == NULL ) {
        ap_log_error( APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(03089)
                     "initializing post config dry run");
        apr_pool_userdata_set((const void *)1, mod_h2_init_key,
                              apr_pool_cleanup_null, s->process->pool);
        return APR_SUCCESS;
    }
    
    ngh2 = nghttp2_version(0);
    ap_log_error( APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(03090)
                 "mod_http2 (v%s, feats=%s%s%s%s, nghttp2 %s), initializing...",
                 MOD_HTTP2_VERSION, 
                 myfeats.change_prio? "CHPRIO"  : "", 
                 myfeats.sha256?      "+SHA256" : "",
                 myfeats.inv_headers? "+INVHD"  : "",
                 myfeats.dyn_windows? "+DWINS"  : "",
                 ngh2?                ngh2->version_str : "unknown");
    
    switch (h2_conn_mpm_type()) {
        case H2_MPM_SIMPLE:
        case H2_MPM_MOTORZ:
        case H2_MPM_NETWARE:
        case H2_MPM_WINNT:
            /* not sure we need something extra for those. */
            break;
        case H2_MPM_EVENT:
        case H2_MPM_WORKER:
            /* all fine, we know these ones */
            break;
        case H2_MPM_PREFORK:
            /* ok, we now know how to handle that one */
            break;
        case H2_MPM_UNKNOWN:
            /* ??? */
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(03091)
                         "post_config: mpm type unknown");
            break;
    }
    
    if (!h2_mpm_supported() && !mpm_warned) {
        mpm_warned = 1;
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(10034)
                     "The mpm module (%s) is not supported by mod_http2. The mpm determines "
                     "how things are processed in your server. HTTP/2 has more demands in "
                     "this regard and the currently selected mpm will just not do. "
                     "This is an advisory warning. Your server will continue to work, but "
                     "the HTTP/2 protocol will be inactive.", 
                     h2_conn_mpm_name());
    }
    
    status = h2_h2_init(p, s);
    if (status == APR_SUCCESS) {
        status = h2_switch_init(p, s);
    }
    if (status == APR_SUCCESS) {
        status = h2_task_init(p, s);
    }
    
    return status;
}