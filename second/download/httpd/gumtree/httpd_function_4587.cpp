static int ap_session_save(request_rec * r, session_rec * z)
{
    if (z) {
        apr_time_t now = apr_time_now();
        int rv = 0;

        session_dir_conf *dconf = ap_get_module_config(r->per_dir_config,
                                                       &session_module);

        /* sanity checks, should we try save at all? */
        if (z->written) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, SESSION_PREFIX
                          "attempt made to save the session twice, "
                          "session not saved: %s", r->uri);
            return APR_EGENERAL;
        }
        if (z->expiry && z->expiry < now) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, SESSION_PREFIX
                          "attempt made to save a session when the session had already expired, "
                          "session not saved: %s", r->uri);
            return APR_EGENERAL;
        }

        /* reset the expiry back to maxage, if the expiry is present */
        if (dconf->maxage) {
            z->expiry = now + dconf->maxage * APR_USEC_PER_SEC;
            z->maxage = dconf->maxage;
        }

        /* encode the session */
        rv = ap_run_session_encode(r, z);
        if (OK != rv) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, SESSION_PREFIX
                          "error while encoding the session, "
                          "session not saved: %s", r->uri);
            return rv;
        }

        /* try the save */
        rv = ap_run_session_save(r, z);
        if (DECLINED == rv) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, SESSION_PREFIX
                          "session is enabled but no session modules have been configured, "
                          "session not saved: %s", r->uri);
            return APR_EGENERAL;
        }
        else if (OK != rv) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, SESSION_PREFIX
                          "error while saving the session, "
                          "session not saved: %s", r->uri);
            return rv;
        }
        else {
            z->written = 1;
        }
    }

    return APR_SUCCESS;

}