static dav_error * dav_propdb_open(apr_pool_t *pool,
                                   const dav_resource *resource, int ro,
                                   dav_db **pdb)
{
    dav_db *db;
    dav_error *err;
    apr_datum_t key;
    apr_datum_t value = { 0 };

    *pdb = NULL;

    /*
    ** Return if an error occurred, or there is no database.
    **
    ** NOTE: db could be NULL if we attempted to open a readonly
    **       database that doesn't exist. If we require read/write
    **       access, then a database was created and opened.
    */
    if ((err = dav_dbm_open(pool, resource, ro, &db)) != NULL
        || db == NULL)
        return err;

    db->uri_index = apr_hash_make(pool);

    key.dptr = DAV_GDBM_NS_KEY;
    key.dsize = DAV_GDBM_NS_KEY_LEN;
    if ((err = dav_dbm_fetch(db, key, &value)) != NULL) {
        /* ### push a higher-level description? */
        return err;
    }

    if (value.dptr == NULL) {
        dav_propdb_metadata m = {
            DAV_DBVSN_MAJOR, DAV_DBVSN_MINOR, 0
        };

        /*
        ** If there is no METADATA key, then the database may be
        ** from versions 0.9.0 .. 0.9.4 (which would be incompatible).
        ** These can be identified by the presence of an NS_TABLE entry.
        */
        key.dptr = "NS_TABLE";
        key.dsize = 8;
        if (dav_dbm_exists(db, key)) {
            dav_dbm_close(db);

            /* call it a major version error */
            return dav_new_error(pool, HTTP_INTERNAL_SERVER_ERROR,
                                 DAV_ERR_PROP_BAD_MAJOR,
                                 "Prop database has the wrong major "
                                 "version number and cannot be used.");
        }

        /* initialize a new metadata structure */
        dav_set_bufsize(pool, &db->ns_table, sizeof(m));
        memcpy(db->ns_table.buf, &m, sizeof(m));
    }
    else {
        dav_propdb_metadata m;
        int ns;
        const char *uri;

        dav_set_bufsize(pool, &db->ns_table, value.dsize);
        memcpy(db->ns_table.buf, value.dptr, value.dsize);

        memcpy(&m, value.dptr, sizeof(m));
        if (m.major != DAV_DBVSN_MAJOR) {
            dav_dbm_close(db);

            return dav_new_error(pool, HTTP_INTERNAL_SERVER_ERROR,
                                 DAV_ERR_PROP_BAD_MAJOR,
                                 "Prop database has the wrong major "
                                 "version number and cannot be used.");
        }
        db->version = m.minor;
        db->ns_count = ntohs(m.ns_count);

        dav_dbm_freedatum(db, value);

        /* create db->uri_index */
        for (ns = 0, uri = db->ns_table.buf + sizeof(dav_propdb_metadata);
             ns++ < db->ns_count;
             uri += strlen(uri) + 1) {

            /* we must copy the key, in case ns_table.buf moves */
            apr_hash_set(db->uri_index,
                         apr_pstrdup(pool, uri), APR_HASH_KEY_STRING,
                         (void *)ns);
        }
    }

    *pdb = db;
    return NULL;
}