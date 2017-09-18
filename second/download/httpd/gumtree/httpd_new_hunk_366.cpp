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
                             mc->szSessionCacheDataFile,
                             mc->pPool)) != APR_SUCCESS) {
        char buf[100];
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "Cannot allocate shared memory: (%d)%s", rv,
                     apr_strerror(rv, buf, sizeof(buf)));
        ssl_die();
    }
    shm_segment = apr_shm_baseaddr_get(mc->pSessionCacheDataMM);
    shm_segsize = apr_shm_size_get(mc->pSessionCacheDataMM);

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "shmcb_init allocated %u bytes of shared memory",
                 shm_segsize);
    if (!shmcb_init_memory(s, shm_segment, shm_segsize)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "Failure initialising 'shmcb' shared memory");
        ssl_die();
    }
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                 "Shared memory session cache initialised");

    /* 
     * Success ... we hack the memory block into place by cheating for
     * now and stealing a member variable the original shared memory
     * cache was using. :-)
     */
