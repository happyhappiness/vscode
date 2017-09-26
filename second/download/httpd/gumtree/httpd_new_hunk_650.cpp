#error APR random number support is missing; you probably need to install the truerand library.
#endif

    if (status != APR_SUCCESS) {
        char buf[120];
        ap_log_error(APLOG_MARK, APLOG_CRIT, status, s,
                     "Digest: error generating secret: %s",
                     apr_strerror(status, buf, sizeof(buf)));
        return status;
    }

    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, "Digest: done");

