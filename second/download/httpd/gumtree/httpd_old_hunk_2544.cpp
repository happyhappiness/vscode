        }

        /* pass 1: scan DBM database */
        keyidx = 0;
        if ((rv = apr_dbm_open(&dbm, ctx->data_file, APR_DBM_RWCREATE,
                               DBM_FILE_MODE, ctx->pool)) != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                         "Cannot open socache DBM file `%s' for "
                         "scanning",
                         ctx->data_file);
            break;
        }
        apr_dbm_firstkey(dbm, &dbmkey);
