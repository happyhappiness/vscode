            apr_pool_destroy(p);
            break;
        }

        /* pass 1: scan DBM database */
        keyidx = 0;
        if (apr_dbm_open(&dbm, mc->szSessionCacheDataFile,
		APR_DBM_RWCREATE,SSL_DBM_FILE_MODE, p) != APR_SUCCESS) {
            ssl_log(s, SSL_LOG_ERROR|SSL_ADD_ERRNO,
                    "Cannot open SSLSessionCache DBM file `%s' for scanning",
                    mc->szSessionCacheDataFile);
            apr_pool_destroy(p);
            break;
        }
        apr_dbm_firstkey(dbm, &dbmkey);
        while (dbmkey.dptr != NULL) {
            nElements++;
