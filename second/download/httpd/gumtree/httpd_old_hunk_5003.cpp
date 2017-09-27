    if (!zz || (zz->expiry && zz->expiry < now)) {

        /* no luck, create a blank session */
        zz = (session_rec *) apr_pcalloc(r->pool, sizeof(session_rec));
        zz->pool = r->pool;
        zz->entries = apr_table_make(zz->pool, 10);
        zz->uuid = (apr_uuid_t *) apr_pcalloc(zz->pool, sizeof(apr_uuid_t));
        apr_uuid_get(zz->uuid);

    }
    else {
        rv = ap_run_session_decode(r, zz);
        if (OK != rv) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01817)
