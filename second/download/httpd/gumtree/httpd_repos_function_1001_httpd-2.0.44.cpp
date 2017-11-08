static char *lookup_map_dbmfile(request_rec *r, const char *file, 
                                const char *dbmtype, char *key)
{
    apr_dbm_t *dbmfp = NULL;
    apr_datum_t dbmkey;
    apr_datum_t dbmval;
    char *value = NULL;
    char buf[MAX_STRING_LEN];
    apr_status_t rv;

    dbmkey.dptr  = key;
    dbmkey.dsize = strlen(key);
    if ((rv = apr_dbm_open_ex(&dbmfp, dbmtype, file, APR_DBM_READONLY, 
                              0 /* irrelevant when reading */, r->pool)) == APR_SUCCESS) {
        rv = apr_dbm_fetch(dbmfp, dbmkey, &dbmval);
        if (rv == APR_SUCCESS && dbmval.dptr) {
            memcpy(buf, dbmval.dptr, 
                   dbmval.dsize < sizeof(buf)-1 ? 
                   dbmval.dsize : sizeof(buf)-1  );
            buf[dbmval.dsize] = '\0';
            value = apr_pstrdup(r->pool, buf);
        }
        apr_dbm_close(dbmfp);
    }
    return value;
}