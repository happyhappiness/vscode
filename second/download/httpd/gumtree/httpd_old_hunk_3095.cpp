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

