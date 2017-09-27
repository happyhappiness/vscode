        }
        apr_dbm_close(dbm);

        /* pass 2: delete expired elements */
        if (apr_dbm_open(&dbm, ctx->data_file, APR_DBM_RWCREATE,
                         DBM_FILE_MODE, ctx->pool) != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                         "Cannot re-open socache DBM file `%s' for "
                         "expiring",
                         ctx->data_file);
            break;
        }
        for (i = 0; i < keyidx; i++) {
