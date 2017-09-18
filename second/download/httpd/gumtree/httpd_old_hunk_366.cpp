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
                             mc->szSessionCacheDataFile,
                             mc->pPool)) != APR_SUCCESS) {
        char buf[100];
        ssl_log(s, SSL_LOG_ERROR,
                "Cannot allocate shared memory: (%d)%s", rv,
                apr_strerror(rv, buf, sizeof(buf)));
        ssl_die();
    }
    shm_segment = apr_shm_baseaddr_get(mc->pSessionCacheDataMM);
    shm_segsize = apr_shm_size_get(mc->pSessionCacheDataMM);

    ssl_log(s, SSL_LOG_TRACE, "shmcb_init allocated %u bytes of shared "
            "memory", shm_segsize);
    if (!shmcb_init_memory(s, shm_segment, shm_segsize)) {
        ssl_log(s, SSL_LOG_ERROR,
                "Failure initialising 'shmcb' shared memory");
        ssl_die();
    }
    ssl_log(s, SSL_LOG_INFO, "Shared memory session cache initialised");

    /* 
     * Success ... we hack the memory block into place by cheating for
     * now and stealing a member variable the original shared memory
     * cache was using. :-)
     */
