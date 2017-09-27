    apr_status_t rv;

    elts = 0;
    size = 0;

    apr_pool_clear(ctx->pool);
    if ((rv = apr_dbm_open(&dbm, ctx->data_file, APR_DBM_RWCREATE, 
                           DBM_FILE_MODE, ctx->pool)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                     "Cannot open socache DBM file `%s' for status "
                     "retrival",
                     ctx->data_file);
        return;
    }
    /*
