static dav_error * dav_dbm_firstkey(dav_db *db, apr_datum_t *pkey)
{
    apr_status_t status = apr_dbm_firstkey(db->file, pkey);

    return dav_fs_dbm_error(db, NULL, status);
}