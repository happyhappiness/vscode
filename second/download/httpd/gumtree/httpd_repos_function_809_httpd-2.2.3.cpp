void ssl_scache_shmcb_init(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);
    void *shm_segment;
    apr_size_t shm_segsize;
    apr_status_t rv;

    /*
     * Create shared memory segment
     */
    if (mc->szSessionCacheDataFile == NULL) {
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
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "Cannot allocate shared memory: (%d)%s", rv,
                     apr_strerror(rv, buf, sizeof(buf)));
        ssl_die();
    }
    shm_segment = apr_shm_baseaddr_get(mc->pSessionCacheDataMM);
    shm_segsize = apr_shm_size_get(mc->pSessionCacheDataMM);

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "shmcb_init allocated %" APR_SIZE_T_FMT
                 " bytes of shared memory",
                 shm_segsize);
    if (!shmcb_init_memory(s, shm_segment, shm_segsize)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "Failure initialising 'shmcb' shared memory");
        ssl_die();
    }
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                 "Shared memory session cache initialised");

    /*
     * Success ...
     */
    mc->tSessionCacheDataTable = shm_segment;
    return;
}