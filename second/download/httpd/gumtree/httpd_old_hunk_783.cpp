        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "SSLSessionCache required");
        ssl_die();
    }

    /* Use anonymous shm by default, fall back on name-based. */
    rv = apr_shm_create(&(mc->pSessionCacheDataMM), 
                        mc->nSessionCacheDataSize, 
                        NULL, mc->pPool);
    
    if (APR_STATUS_IS_ENOTIMPL(rv)) {
        rv = apr_shm_create(&(mc->pSessionCacheDataMM), 
                            mc->nSessionCacheDataSize, 
                            mc->szSessionCacheDataFile,
                            mc->pPool);
    }

    if (rv != APR_SUCCESS) {
        char buf[100];
