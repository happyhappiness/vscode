static dav_error * dav_propdb_output_value(dav_db *db,
                                           const dav_prop_name *name,
                                           dav_xmlns_info *xi,
                                           apr_text_header *phdr,
                                           int *found)
{
    apr_datum_t key = dav_build_key(db, name);
    apr_datum_t value;
    dav_error *err;

    if ((err = dav_dbm_fetch(db, key, &value)) != NULL)
        return err;
    if (value.dptr == NULL) {
        *found = 0;
        return NULL;
    }
    *found = 1;

    dav_append_prop(db->pool, key.dptr, value.dptr, phdr);

    dav_dbm_freedatum(db, value);

    return NULL;
}