static dav_error * dav_propdb_next_name(dav_db *db, dav_prop_name *pname)
{
    dav_error *err;

    /* free the previous key. note: if the loop is aborted, then the DBM
       will toss the key (via pool cleanup) */
    if (db->iter.dptr != NULL)
        dav_dbm_freedatum(db, db->iter);

    if ((err = dav_dbm_nextkey(db, &db->iter)) != NULL)
        return err;

    /* skip past the METADATA key */
    if (db->iter.dptr != NULL && *db->iter.dptr == 'M')
        return dav_propdb_next_name(db, pname);

    dav_set_name(db, pname);
    return NULL;
}