
#define KEYMAX 1024

    ssl_mutex_on(s);
    for (;;) {
        /* allocate the key array in a memory sub pool */
        apr_pool_sub_make(&p, mc->pPool, NULL);
        if (p == NULL)
            break;
        if ((keylist = apr_palloc(p, sizeof(dbmkey)*KEYMAX)) == NULL) {
            apr_pool_destroy(p);
            break;
        }

        /* pass 1: scan DBM database */
        keyidx = 0;
        if ((rv = apr_dbm_open(&dbm, mc->szSessionCacheDataFile, 
                               APR_DBM_RWCREATE,SSL_DBM_FILE_MODE,
                               p)) != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                         "Cannot open SSLSessionCache DBM file `%s' for "
                         "scanning",
                         mc->szSessionCacheDataFile);
