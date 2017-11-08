static void dav_propdb_close(dav_db *db)
{

    if (db->ns_table_dirty) {
        dav_propdb_metadata m;
        apr_datum_t key;
        apr_datum_t value;
        dav_error *err;

        key.dptr = DAV_GDBM_NS_KEY;
        key.dsize = DAV_GDBM_NS_KEY_LEN;

        value.dptr = db->ns_table.buf;
        value.dsize = db->ns_table.cur_len;

        /* fill in the metadata that we store into the prop db. */
        m.major = DAV_DBVSN_MAJOR;
        m.minor = db->version;          /* ### keep current minor version? */
        m.ns_count = htons(db->ns_count);

        memcpy(db->ns_table.buf, &m, sizeof(m));

        err = dav_dbm_store(db, key, value);
        if (err != NULL)
            ap_log_error(APLOG_MARK, APLOG_WARNING, err->aprerr, ap_server_conf,
                         APLOGNO(00577) "Error writing propdb: %s", err->desc);
    }

    dav_dbm_close(db);
}