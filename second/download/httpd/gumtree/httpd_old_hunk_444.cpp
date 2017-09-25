    if (mc->szSessionCacheDataFile == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "SSLSessionCache required");
        ssl_die();
    }

    if ((rv = apr_shm_create(&(mc->pSessionCacheDataMM), 
                             mc->nSessionCacheDataSize, 
                             mc->szSessionCacheDataFile,
                             mc->pPool)) != APR_SUCCESS) {
        char buf[100];
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "Cannot allocate shared memory: (%d)%s", rv,
                     apr_strerror(rv, buf, sizeof(buf)));
        ssl_die();
    }
