dav_error * dav_dbm_delete(dav_db *db, apr_datum_t key)
{
    apr_status_t status = apr_dbm_delete(db->file, key);

    return dav_fs_dbm_error(db, NULL, status);
}