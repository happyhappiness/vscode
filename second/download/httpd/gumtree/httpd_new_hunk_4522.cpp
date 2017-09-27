                                  apr_read_type_e block,
                                  apr_off_t readbytes) 
{
    h2_filter_cin *cin = f->ctx;
    apr_status_t status = APR_SUCCESS;
    apr_interval_time_t saved_timeout = UNSET;
    const int trace1 = APLOGctrace1(f->c);
    
    if (trace1) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                      "h2_session(%ld): read, %s, mode=%d, readbytes=%ld", 
                      (long)f->c->id, (block == APR_BLOCK_READ)? 
                      "BLOCK_READ" : "NONBLOCK_READ", mode, (long)readbytes);
    }
    
    if (mode == AP_MODE_INIT || mode == AP_MODE_SPECULATIVE) {
        return ap_get_brigade(f->next, brigade, mode, block, readbytes);
    }
    
    if (mode != AP_MODE_READBYTES) {
        return (block == APR_BLOCK_READ)? APR_SUCCESS : APR_EAGAIN;
    }
    
    if (!cin->bb) {
        cin->bb = apr_brigade_create(cin->session->pool, f->c->bucket_alloc);
    }

    if (!cin->socket) {
        cin->socket = ap_get_conn_socket(f->c);
    }
    
    if (APR_BRIGADE_EMPTY(cin->bb)) {
        /* We only do a blocking read when we have no streams to process. So,
         * in httpd scoreboard lingo, we are in a KEEPALIVE connection state.
         */
        if (block == APR_BLOCK_READ) {
            if (cin->timeout > 0) {
                apr_socket_timeout_get(cin->socket, &saved_timeout);
                apr_socket_timeout_set(cin->socket, cin->timeout);
            }
