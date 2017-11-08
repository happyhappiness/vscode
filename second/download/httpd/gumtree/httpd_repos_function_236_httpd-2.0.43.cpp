static dav_error * dav_propdb_remove(dav_db *db, const dav_prop_name *name)
{
    apr_datum_t key = dav_build_key(db, name);
    return dav_dbm_delete(db, key);
}