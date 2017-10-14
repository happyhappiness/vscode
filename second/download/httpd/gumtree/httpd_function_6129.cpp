static int h2_protocol_switch(conn_rec *c, request_rec *r, server_rec *s,
                              const char *protocol)
{
    int found = 0;
    const char **protos = h2_h2_is_tls(c)? h2_tls_protos : h2_clear_protos;
    const char **p = protos;
    
    (void)s;
    while (*p) {
        if (!strcmp(*p, protocol)) {
            found = 1;
            break;
        }
        p++;
    }
    
    if (found) {
        h2_ctx *ctx = h2_ctx_get(c);
        
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                      "switching protocol to '%s'", protocol);
        h2_ctx_protocol_set(ctx, protocol);
        h2_ctx_server_set(ctx, s);
        
        if (r != NULL) {
            apr_status_t status;
            /* Switching in the middle of a request means that
             * we have to send out the response to this one in h2
             * format. So we need to take over the connection
             * right away.
             */
            ap_remove_input_filter_byhandle(r->input_filters, "http_in");
            ap_remove_input_filter_byhandle(r->input_filters, "reqtimeout");
            ap_remove_output_filter_byhandle(r->output_filters, "HTTP_HEADER");
            
            /* Ok, start an h2_conn on this one. */
            status = h2_conn_process(r->connection, r, r->server);
            if (status != DONE) {
                /* Nothing really to do about this. */
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r,
                              "session proessed, unexpected status");
            }
        }
        return DONE;
    }
    
    return DECLINED;
}