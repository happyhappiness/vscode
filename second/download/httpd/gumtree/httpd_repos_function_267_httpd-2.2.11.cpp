dav_error * dav_dbm_fetch(dav_db *db, apr_datum_t key, apr_datum_t *pvalue)
{
    apr_status_t status = apr_dbm_fetch(db->file, key, pvalue);

    return dav_fs_dbm_error(db, NULL, status);
}