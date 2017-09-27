                                const char *dbmtype, char *key)
{
    apr_dbm_t *dbmfp = NULL;
    apr_datum_t dbmkey;
    apr_datum_t dbmval;
    char *value;

    if (apr_dbm_open_ex(&dbmfp, dbmtype, file, APR_DBM_READONLY, APR_OS_DEFAULT,
                        r->pool) != APR_SUCCESS) {
        return NULL;
    }

    dbmkey.dptr  = key;
    dbmkey.dsize = strlen(key);

