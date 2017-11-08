void ssl_scache_shmht_init(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);
    table_t *ta;
    int ta_errno;
    apr_size_t avail;
    int n;
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
    n = n < 10 ? 10 : n;

    /*
     * Passing server_rec as opt_param to table_alloc so that we can do
     * logging if required ssl_util_table. Otherwise, mc is sufficient.
     */ 
    if ((ta = table_alloc(n, &ta_errno, 
                          ssl_scache_shmht_malloc,  
                          ssl_scache_shmht_calloc, 
                          ssl_scache_shmht_realloc, 
                          ssl_scache_shmht_free, s )) == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "Cannot allocate hash table in shared memory: %s",
                     table_strerror(ta_errno));
        ssl_die();
    }

    table_attr(ta, TABLE_FLAG_AUTO_ADJUST|TABLE_FLAG_ADJUST_DOWN);
    table_set_data_alignment(ta, sizeof(char *));
    table_clear(ta);
    mc->tSessionCacheDataTable = ta;

    /*
     * Log the done work
     */
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, 
                 "Init: Created hash-table (%d buckets) "
                 "in shared memory (%" APR_SIZE_T_FMT 
                 " bytes) for SSL session cache",
                 n, avail);
    return;
}