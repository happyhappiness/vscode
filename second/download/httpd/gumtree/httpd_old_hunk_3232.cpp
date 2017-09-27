        stapling_mutex_off(s);
        return SSL_TLSEXT_ERR_ALERT_FATAL;
    }

    if (rsp) {
        /* see if response is acceptable */
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "stapling_cb: retrieved cached response");
        rv = stapling_check_response(s, mctx, cinf, rsp, NULL);
        if (rv == SSL_TLSEXT_ERR_ALERT_FATAL) {
            OCSP_RESPONSE_free(rsp);
            stapling_mutex_off(s);
            return SSL_TLSEXT_ERR_ALERT_FATAL;
