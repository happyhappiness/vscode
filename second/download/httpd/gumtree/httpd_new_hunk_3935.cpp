        return SSL_TLSEXT_ERR_NOACK;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01952)
                 "stapling_cb: retrieved cached certificate data");

    rv = get_and_check_cached_response(s, mctx, &rsp, &ok, cinf, conn->pool);
    if (rv != 0) {
        return rv;
    }

    if (rsp == NULL) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01954)
                     "stapling_cb: renewing cached response");
        stapling_refresh_mutex_on(s);
        /* Maybe another request refreshed the OCSP response while this
         * thread waited for the mutex.  Check again.
         */
        rv = get_and_check_cached_response(s, mctx, &rsp, &ok, cinf,
                                           conn->pool);
        if (rv != 0) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "stapling_cb: error checking for cached response "
                         "after obtaining refresh mutex");
            stapling_refresh_mutex_off(s);
            return rv;
