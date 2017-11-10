static dav_error * dav_dbm_nextkey(dav_db *db, apr_datum_t *pkey)
{
    apr_status_t status = apr_dbm_nextkey(db->file, pkey);

    return dav_fs_dbm_error(db, NULL, status);
}