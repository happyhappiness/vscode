static char *lookup_map_dbmfile(request_rec *r, const char *file,
                                const char *dbmtype, char *key)
{
    apr_dbm_t *dbmfp = NULL;
    apr_datum_t dbmkey;
    apr_datum_t dbmval;
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

    if (apr_dbm_fetch(dbmfp, dbmkey, &dbmval) == APR_SUCCESS && dbmval.dptr) {
        value = apr_pstrmemdup(r->pool, dbmval.dptr, dbmval.dsize);
    }
    else {
        value = NULL;
    }

    apr_dbm_close(dbmfp);

    return value;
}