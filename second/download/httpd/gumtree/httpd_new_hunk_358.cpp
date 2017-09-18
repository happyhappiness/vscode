
    /*
     * Warn the user that he should use the session cache.
     * But we can operate without it, of course.
     */
    if (mc->nSessionCacheMode == SSL_SCMODE_UNSET) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                     "Init: Session Cache is not configured "
                     "[hint: SSLSessionCache]");
        mc->nSessionCacheMode = SSL_SCMODE_NONE;
        return;
    }

    if (mc->nSessionCacheMode == SSL_SCMODE_DBM)
        ssl_scache_dbm_init(s, p);
