static apr_status_t session_receive(const char *data, apr_size_t len,
                                    apr_size_t *readlen, int *done,
                                    void *puser)
{
    h2_session *session = (h2_session *)puser;
    AP_DEBUG_ASSERT(session);
    if (len > 0) {
        ssize_t n = nghttp2_session_mem_recv(session->ngh2,
                                             (const uint8_t *)data, len);
        if (n < 0) {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, APR_EGENERAL,
                          session->c,
                          "h2_session: nghttp2_session_mem_recv error %d",
                          (int)n);
            if (nghttp2_is_fatal((int)n)) {
                *done = 1;
                h2_session_abort_int(session, (int)n);
                return APR_EGENERAL;
            }
        }
        else {
            *readlen = n;
        }
    }
    return APR_SUCCESS;
}