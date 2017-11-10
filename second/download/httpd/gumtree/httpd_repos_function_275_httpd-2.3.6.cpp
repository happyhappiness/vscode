int dav_dbm_exists(dav_db *db, apr_datum_t key)
{
    return apr_dbm_exists(db->file, key);
}