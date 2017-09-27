            z->maxage = dconf->maxage;
        }

        /* encode the session */
        rv = ap_run_session_encode(r, z);
        if (OK != rv) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01820)
                          "error while encoding the session, "
                          "session not saved: %s", r->uri);
            return rv;
        }

        /* try the save */
        rv = ap_run_session_save(r, z);
        if (DECLINED == rv) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01821)
                          "session is enabled but no session modules have been configured, "
                          "session not saved: %s", r->uri);
            return APR_EGENERAL;
        }
        else if (OK != rv) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01822)
                          "error while saving the session, "
                          "session not saved: %s", r->uri);
            return rv;
        }
        else {
            z->written = 1;
