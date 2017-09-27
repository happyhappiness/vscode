    ap_dbd_t *rec;
    apr_status_t rv;
    const char *err = "";

    rv = apr_pool_create(&rec_pool, pool);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, cfg->server, APLOGNO(00624)
                     "Failed to create memory pool");
        return rv;
    }

    rec = apr_pcalloc(rec_pool, sizeof(ap_dbd_t));

    rec->pool = rec_pool;
