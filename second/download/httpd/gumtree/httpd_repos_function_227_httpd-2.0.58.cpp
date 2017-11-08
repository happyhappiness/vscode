dav_error * dav_dbm_store(dav_db *db, apr_datum_t key, apr_datum_t value)
{
    apr_status_t status = apr_dbm_store(db->file, key, value);

    return dav_fs_dbm_error(db, NULL, status);
}