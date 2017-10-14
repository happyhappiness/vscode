static int ap_session_load(request_rec * r, session_rec ** z)
{

    session_dir_conf *dconf = ap_get_module_config(r->per_dir_config,
                                                   &session_module);
    apr_time_t now;
    session_rec *zz = NULL;
    int rv = 0;

    /* is the session enabled? */
    if (!dconf || !dconf->enabled) {
        return APR_SUCCESS;
    }

    /* should the session be loaded at all? */
    if (!session_included(r, dconf)) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, SESSION_PREFIX
                      "excluded by configuration for: %s", r->uri);
        return APR_SUCCESS;
    }

    /* load the session from the session hook */
    rv = ap_run_session_load(r, &zz);
    if (DECLINED == rv) {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, SESSION_PREFIX
                      "session is enabled but no session modules have been configured, "
                      "session not loaded: %s", r->uri);
        return APR_EGENERAL;
    }
    else if (OK != rv) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, SESSION_PREFIX
                      "error while loading the session, "
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
        zz->uuid = (apr_uuid_t *) apr_pcalloc(zz->pool, sizeof(apr_uuid_t));
        apr_uuid_get(zz->uuid);

    }
    else {
        rv = ap_run_session_decode(r, zz);
        if (OK != rv) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, SESSION_PREFIX
                          "error while decoding the session, "
                          "session not loaded: %s", r->uri);
            return rv;
        }
    }

    /* make sure the expiry is set, if present */
    if (!zz->expiry && dconf->maxage) {
        zz->expiry = now + dconf->maxage * APR_USEC_PER_SEC;
        zz->maxage = dconf->maxage;
    }

    *z = zz;

    return APR_SUCCESS;

}