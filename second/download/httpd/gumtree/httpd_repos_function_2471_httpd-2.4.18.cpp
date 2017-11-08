apr_status_t h2_session_abort(h2_session *session, apr_status_t reason, int rv)
{
    AP_DEBUG_ASSERT(session);
    if (rv == 0) {
        rv = NGHTTP2_ERR_PROTO;
        switch (reason) {
            case APR_ENOMEM:
                rv = NGHTTP2_ERR_NOMEM;
                break;
            case APR_SUCCESS:                            /* all fine, just... */
            case APR_EOF:                         /* client closed its end... */
            case APR_TIMEUP:                          /* got bored waiting... */
                rv = 0;                            /* ...gracefully shut down */
                break;
            case APR_EBADF:        /* connection unusable, terminate silently */
            default:
                if (APR_STATUS_IS_ECONNABORTED(reason)
                    || APR_STATUS_IS_ECONNRESET(reason)
                    || APR_STATUS_IS_EBADF(reason)) {
                    rv = NGHTTP2_ERR_EOF;
                }
                break;
        }
    }
    return h2_session_abort_int(session, rv);
}