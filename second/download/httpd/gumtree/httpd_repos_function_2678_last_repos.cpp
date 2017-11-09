static ssize_t raw_send(nghttp2_session *ngh2, const uint8_t *data,
                        size_t length, int flags, void *user_data)
{
    h2_proxy_session *session = user_data;
    apr_bucket *b;
    apr_status_t status;
    int flush = 1;

    if (data) {
        b = apr_bucket_transient_create((const char*)data, length, 
                                        session->c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(session->output, b);
    }

    status = proxy_pass_brigade(session->c->bucket_alloc,  
                                session->p_conn, session->c, 
                                session->output, flush);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, session->c, 
                  "h2_proxy_sesssion(%s): raw_send %d bytes, flush=%d", 
                  session->id, (int)length, flush);
    if (status != APR_SUCCESS) {
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    return length;
}