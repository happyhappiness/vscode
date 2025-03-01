    char *value;
    apr_status_t rv;

    if ((rv = apr_dbm_open_ex(&dbmfp, dbmtype, file, APR_DBM_READONLY,
                              APR_OS_DEFAULT, r->pool)) != APR_SUCCESS)
    {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "mod_rewrite: can't open DBM RewriteMap %s", file);
        return NULL;
    }

    dbmkey.dptr  = key;
    dbmkey.dsize = strlen(key);
