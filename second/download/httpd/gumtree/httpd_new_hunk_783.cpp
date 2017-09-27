        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "SSLSessionCache required");
        ssl_die();
    }

    /* Use anonymous shm by default, fall back on name-based. */
    rv = apr_shm_create(&(mc->pSessionCacheDataMM),
                        mc->nSessionCacheDataSize,
                        NULL, mc->pPool);

    if (APR_STATUS_IS_ENOTIMPL(rv)) {
        /* For a name-based segment, remove it first in case of a
         * previous unclean shutdown. */
        apr_shm_remove(mc->szSessionCacheDataFile, mc->pPool);

        rv = apr_shm_create(&(mc->pSessionCacheDataMM),
                            mc->nSessionCacheDataSize,
                            mc->szSessionCacheDataFile,
                            mc->pPool);
    }

    if (rv != APR_SUCCESS) {
        char buf[100];
