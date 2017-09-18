        }
        apr_dbm_close(dbm);

        /* pass 2: delete expired elements */
        if (apr_dbm_open(&dbm, mc->szSessionCacheDataFile,
		APR_DBM_RWCREATE,SSL_DBM_FILE_MODE, p) != APR_SUCCESS) {
            ssl_log(s, SSL_LOG_ERROR|SSL_ADD_ERRNO,
                    "Cannot re-open SSLSessionCache DBM file `%s' for expiring",
                    mc->szSessionCacheDataFile);
            apr_pool_destroy(p);
            break;
        }
        for (i = 0; i < keyidx; i++) {
            apr_dbm_delete(dbm, keylist[i]);
            nDeleted++;
