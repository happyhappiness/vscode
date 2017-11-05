static apr_status_t h2_proxy_session_read(h2_proxy_session *session, int block, 
                                          apr_interval_time_t timeout)
{
    apr_status_t status = APR_SUCCESS;
    
    if (APR_BRIGADE_EMPTY(session->input)) {
        apr_socket_t *socket = NULL;
        apr_time_t save_timeout = -1;
        
        if (block) {
            socket = ap_get_conn_socket(session->c);
            if (socket) {
                apr_socket_timeout_get(socket, &save_timeout);
                apr_socket_timeout_set(socket, timeout);
            }
            else {
                /* cannot block on timeout */
                ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, session->c, APLOGNO(03379)
                              "h2_proxy_session(%s): unable to get conn socket", 
                              session->id);
                return APR_ENOTIMPL;
            }
        }
        
        status = ap_get_brigade(session->c->input_filters, session->input, 
                                AP_MODE_READBYTES, 
                                block? APR_BLOCK_READ : APR_NONBLOCK_READ, 
                                64 * 1024);
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, session->c, 
                      "h2_proxy_session(%s): read from conn", session->id);
        if (socket && save_timeout != -1) {
            apr_socket_timeout_set(socket, save_timeout);
        }
    }
    
    if (status == APR_SUCCESS) {
        status = feed_brigade(session, session->input);
    }
    else if (APR_STATUS_IS_TIMEUP(status)) {
        /* nop */
    }
    else if (!APR_STATUS_IS_EAGAIN(status)) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c, APLOGNO(03380)
                      "h2_proxy_session(%s): read error", session->id);
        dispatch_event(session, H2_PROXYS_EV_CONN_ERROR, status, NULL);
    }

    return status;
}