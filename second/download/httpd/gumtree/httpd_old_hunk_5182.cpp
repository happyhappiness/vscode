                      "session not loaded: %s", r->uri);
        return rv;
    }

    /* found a session that hasn't expired? */
    now = apr_time_now();
    if (!zz || (zz->expiry && zz->expiry < now)) {

        /* no luck, create a blank session */
        zz = (session_rec *) apr_pcalloc(r->pool, sizeof(session_rec));
        zz->pool = r->pool;
        zz->entries = apr_table_make(zz->pool, 10);

    }
    else {
        rv = ap_run_session_decode(r, zz);
        if (OK != rv) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01817)
                          "error while decoding the session, "
                          "session not loaded: %s", r->uri);
            return rv;
        }
    }

    /* make sure the expiry and maxage are set, if present */
    if (dconf->maxage) {
        if (!zz->expiry) {
            zz->expiry = now + dconf->maxage * APR_USEC_PER_SEC;
