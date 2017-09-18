    const char *t;

    if (!(t = ap_auth_type(r)) || strcasecmp(t, "Basic"))
        return DECLINED;

    if (!ap_auth_name(r)) {
        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR,
		    r->server, "need AuthName: %s", r->uri);
        return SERVER_ERROR;
    }

    if (!auth_line) {
        ap_note_basic_auth_failure(r);
        return AUTH_REQUIRED;
    }

    if (strcasecmp(ap_getword(r->pool, &auth_line, ' '), "Basic")) {
        /* Client tried to authenticate using wrong auth scheme */
        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                    "client used wrong authentication scheme: %s", r->uri);
        ap_note_basic_auth_failure(r);
        return AUTH_REQUIRED;
    }

    t = ap_uudecode(r->pool, auth_line);
