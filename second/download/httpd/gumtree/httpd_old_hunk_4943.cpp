    status = apr_generate_random_bytes(secret, sizeof(secret));
#else
#error APR random number support is missing; you probably need to install the truerand library.
#endif

    if (status != APR_SUCCESS) {
        char buf[120];
        ap_log_error(APLOG_MARK, APLOG_CRIT, status, s, APLOGNO(01758)
                     "error generating secret: %s",
                     apr_strerror(status, buf, sizeof(buf)));
        return status;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01759) "done");

    return APR_SUCCESS;
