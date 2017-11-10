void dav_dbm_freedatum(dav_db *db, apr_datum_t data)
{
    apr_dbm_freedatum(db->file, data);
}