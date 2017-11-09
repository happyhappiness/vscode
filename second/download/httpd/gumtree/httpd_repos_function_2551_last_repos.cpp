apr_status_t h2_filter_core_input(ap_filter_t* f,
                                  apr_bucket_brigade* brigade,
                                  ap_input_mode_t mode,
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
        }
        status = ap_get_brigade(f->next, cin->bb, AP_MODE_READBYTES,
                                block, readbytes);
        if (saved_timeout != UNSET) {
            apr_socket_timeout_set(cin->socket, saved_timeout);
        }
    }
    
    switch (status) {
        case APR_SUCCESS:
            status = recv_RAW_brigade(f->c, cin, cin->bb, block);
            break;
        case APR_EOF:
        case APR_EAGAIN:
        case APR_TIMEUP:
            if (trace1) {
                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
                              "h2_session(%ld): read", f->c->id);
            }
            break;
        default:
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, f->c, APLOGNO(03046)
                          "h2_session(%ld): error reading", f->c->id);
            break;
    }
    return status;
}