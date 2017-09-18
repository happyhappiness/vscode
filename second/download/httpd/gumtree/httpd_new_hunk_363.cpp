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
            apr_pool_destroy(p);
            break;
        }
        apr_dbm_firstkey(dbm, &dbmkey);
        while (dbmkey.dptr != NULL) {
            nElements++;
