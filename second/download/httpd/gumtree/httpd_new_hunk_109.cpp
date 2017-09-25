                   mc->nSessionCacheDataSize, mc->pPool)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "Cannot initialize rmm");
        ssl_die();
    }
    ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                 "initialize MM %pp RMM %pp",
                 mc->pSessionCacheDataMM, mc->pSessionCacheDataRMM);

    /*
     * Create hash table in shared memory segment
     */
    avail = mc->nSessionCacheDataSize;
