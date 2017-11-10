dav_error * dav_dbm_fetch(dav_db *db, apr_datum_t key, apr_datum_t *pvalue)
{
    apr_status_t status;

    if (!key.dptr) {
        /* no key could be created (namespace not known) => no value */
        memset(pvalue, 0, sizeof(*pvalue));
        status = APR_SUCCESS;
    } else {
        status = apr_dbm_fetch(db->file, key, pvalue);
    }

    return dav_fs_dbm_error(db, NULL, status);
}