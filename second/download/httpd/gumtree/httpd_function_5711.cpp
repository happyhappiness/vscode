static int get_and_check_cached_response(server_rec *s, modssl_ctx_t *mctx,
                                         OCSP_RESPONSE **rsp, certinfo *cinf, 
                                         apr_pool_t *p)
{
    BOOL ok;
    int rv;

    AP_DEBUG_ASSERT(*rsp == NULL);

    /* Check to see if we already have a response for this certificate */
    stapling_get_cached_response(s, rsp, &ok, cinf, p);

    if (*rsp) {
        /* see if response is acceptable */
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01953)
                     "stapling_cb: retrieved cached response");
        rv = stapling_check_response(s, mctx, cinf, *rsp, NULL);
        if (rv == SSL_TLSEXT_ERR_ALERT_FATAL) {
            OCSP_RESPONSE_free(*rsp);
            *rsp = NULL;
            return SSL_TLSEXT_ERR_ALERT_FATAL;
        }
        else if (rv == SSL_TLSEXT_ERR_NOACK) {
            /* Error in response. If this error was not present when it was
             * stored (i.e. response no longer valid) then it can be
             * renewed straight away.
             *
             * If the error *was* present at the time it was stored then we
             * don't renew the response straight away; we just wait for the
             * cached response to expire.
             */
            if (ok) {
                OCSP_RESPONSE_free(*rsp);
                *rsp = NULL;
            }
            else if (!mctx->stapling_return_errors) {
                OCSP_RESPONSE_free(*rsp);
                *rsp = NULL;
                return SSL_TLSEXT_ERR_NOACK;
            }
        }
    }
    return 0;
}