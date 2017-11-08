static int vt_sdbm_exists(apr_dbm_t *dbm, apr_datum_t key)
{
    int exists;
    apr_sdbm_datum_t ckey;

    CONVERT_DATUM(ckey, &key);

    {
        apr_sdbm_datum_t value;
        if (apr_sdbm_fetch(dbm->file, &value, ckey) != APR_SUCCESS) {
            exists = 0;
        }
        else
            exists = value.dptr != NULL;
    }

    return exists;
}