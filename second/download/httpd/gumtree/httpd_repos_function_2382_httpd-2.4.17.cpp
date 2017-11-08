static ssize_t send_cb(nghttp2_session *ngh2,
                       const uint8_t *data, size_t length,
                       int flags, void *userp)
{
    h2_session *session = (h2_session *)userp;
    apr_status_t status = send_data(session, (const char *)data, length);
    
    (void)ngh2;
    (void)flags;
    if (status == APR_SUCCESS) {
        return length;
    }
    if (status == APR_EAGAIN || status == APR_TIMEUP) {
        return NGHTTP2_ERR_WOULDBLOCK;
    }
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c,
                  "h2_session: send error");
    return h2_session_status_from_apr_status(status);
}