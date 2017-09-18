    apr_status_t rv;

    /*
     * Create shared memory segment
     */
    if (mc->szSessionCacheDataFile == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "SSLSessionCache required");
        ssl_die();
    }

    if ((rv = apr_shm_create(&(mc->pSessionCacheDataMM), 
                   mc->nSessionCacheDataSize, 
                   mc->szSessionCacheDataFile, mc->pPool)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "Cannot allocate shared memory");
        ssl_die();
    }

    if ((rv = apr_rmm_init(&(mc->pSessionCacheDataRMM), NULL,
                   apr_shm_baseaddr_get(mc->pSessionCacheDataMM),
                   mc->nSessionCacheDataSize, mc->pPool)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "Cannot initialize rmm");
        ssl_die();
    }
    ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                 "initialize MM %p RMM %p",
                 mc->pSessionCacheDataMM, mc->pSessionCacheDataRMM);

    /*
     * Create hash table in shared memory segment
     */
    avail = mc->nSessionCacheDataSize;
    n = (avail/2) / 1024;
