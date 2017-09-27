    BOOL rv;
    apr_time_t expiry;

    resp_derlen = i2d_OCSP_RESPONSE(rsp, NULL) + 1;

    if (resp_derlen <= 0) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01927)
                     "OCSP stapling response encode error??");
        return FALSE;
    }

    if (resp_derlen > sizeof resp_der) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01928)
                     "OCSP stapling response too big (%u bytes)", resp_derlen);
        return FALSE;
    }

    p = resp_der;

    /* TODO: potential optimization; _timeout members as apr_interval_time_t */
    if (ok == TRUE) {
        *p++ = 1;
        expiry = apr_time_from_sec(mctx->stapling_cache_timeout);
    }
    else {
        *p++ = 0;
        expiry = apr_time_from_sec(mctx->stapling_errcache_timeout);
    }

    expiry += apr_time_now();
