static apr_datum_t dav_build_key(dav_db *db, const dav_prop_name *name)
{
    char nsbuf[20];
    apr_size_t l_ns, l_name = strlen(name->name);
    apr_datum_t key = { 0 };

    /*
     * Convert namespace ID to a string. "no namespace" is an empty string,
     * so the keys will have the form ":name". Otherwise, the keys will
     * have the form "#:name".
     */
    if (*name->ns == '\0') {
	nsbuf[0] = '\0';
	l_ns = 0;
    }
    else {
        int ns_id = (int)apr_hash_get(db->uri_index, name->ns,
                                      APR_HASH_KEY_STRING);


        if (ns_id == 0) {
            /* the namespace was not found(!) */
            return key;         /* zeroed */
        }

        l_ns = sprintf(nsbuf, "%d", ns_id - 1);
    }

    /* assemble: #:name */
    dav_set_bufsize(db->pool, &db->wb_key, l_ns + 1 + l_name + 1);
    memcpy(db->wb_key.buf, nsbuf, l_ns);
    db->wb_key.buf[l_ns] = ':';
    memcpy(&db->wb_key.buf[l_ns + 1], name->name, l_name + 1);

    /* build the database key */
    key.dsize = l_ns + 1 + l_name + 1;
    key.dptr = db->wb_key.buf;

    return key;
}