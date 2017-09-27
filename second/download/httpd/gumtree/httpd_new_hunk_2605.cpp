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

static dav_error * dav_propdb_define_namespaces(dav_db *db, dav_xmlns_info *xi)
