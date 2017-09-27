                          apr_pool_t *ptemp, server_rec *s)
{
    void *data = NULL;
    const char *mod_h2_init_key = "mod_http2_init_counter";
    nghttp2_info *ngh2;
    apr_status_t status;
    const char *sep = "";
    
    (void)plog;(void)ptemp;
#ifdef H2_NG2_CHANGE_PRIO
    myfeats.change_prio = 1;
    sep = "+";
#endif
#ifdef H2_OPENSSL
    myfeats.sha256 = 1;
#endif
    
    apr_pool_userdata_get(&data, mod_h2_init_key, s->process->pool);
    if ( data == NULL ) {
        ap_log_error( APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(03089)
                     "initializing post config dry run");
        apr_pool_userdata_set((const void *)1, mod_h2_init_key,
