static dav_error * dav_propdb_first_name(dav_db *db, dav_prop_name *pname)
{
    dav_error *err;

    if ((err = dav_dbm_firstkey(db, &db->iter)) != NULL)
        return err;

    /* skip past the METADATA key */
    if (db->iter.dptr != NULL && *db->iter.dptr == 'M')
        return dav_propdb_next_name(db, pname);

    dav_set_name(db, pname);
    return NULL;
}