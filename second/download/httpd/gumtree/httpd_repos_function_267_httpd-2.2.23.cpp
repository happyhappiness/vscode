void dav_dbm_close(dav_db *db)
{
    apr_dbm_close(db->file);
}