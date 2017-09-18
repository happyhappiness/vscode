    apr_status_t rv;

    /*
     * Create shared memory segment
     */
    if (mc->szSessionCacheDataFile == NULL) {
        ssl_log(s, SSL_LOG_ERROR, "SSLSessionCache required");
        ssl_die();
    }

    if ((rv = apr_shm_create(&(mc->pSessionCacheDataMM), 
                   mc->nSessionCacheDataSize, 
                   mc->szSessionCacheDataFile, mc->pPool)) != APR_SUCCESS) {
        ssl_log(s, SSL_LOG_ERROR,
                "Cannot allocate shared memory: %d", rv);
        ssl_die();
    }

    if ((rv = apr_rmm_init(&(mc->pSessionCacheDataRMM), NULL,
                   apr_shm_baseaddr_get(mc->pSessionCacheDataMM),
                   mc->nSessionCacheDataSize, mc->pPool)) != APR_SUCCESS) {
        ssl_log(s, SSL_LOG_ERROR,
                "Cannot initialize rmm: %d", rv);
        ssl_die();
    }
ssl_log(s, SSL_LOG_ERROR, "initialize MM %ld RMM %ld",
        mc->pSessionCacheDataMM, mc->pSessionCacheDataRMM);

    /*
     * Create hash table in shared memory segment
     */
    avail = mc->nSessionCacheDataSize;
    n = (avail/2) / 1024;
