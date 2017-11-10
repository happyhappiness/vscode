static dav_error * dav_propdb_get_rollback(dav_db *db,
                                           const dav_prop_name *name,
                                           dav_deadprop_rollback **prollback)
{
    dav_deadprop_rollback *rb = apr_pcalloc(db->pool, sizeof(*rb));
    apr_datum_t key;
    apr_datum_t value;
    dav_error *err;

    key = dav_build_key(db, name);
    rb->key.dptr = apr_pstrdup(db->pool, key.dptr);
    rb->key.dsize = key.dsize;

    if ((err = dav_dbm_fetch(db, key, &value)) != NULL)
        return err;
    if (value.dptr != NULL) {
        rb->value.dptr = apr_pmemdup(db->pool, value.dptr, value.dsize);
        rb->value.dsize = value.dsize;
    }

    *prollback = rb;
    return NULL;
}