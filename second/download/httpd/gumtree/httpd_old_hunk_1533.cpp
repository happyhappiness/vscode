        ap_note_basic_auth_failure(r);
        return HTTP_UNAUTHORIZED;
    }

    if (strcasecmp(ap_getword(r->pool, &auth_line, ' '), "Basic")) {
        /* Client tried to authenticate using wrong auth scheme */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "client used wrong authentication scheme: %s", r->uri);
        ap_note_basic_auth_failure(r);
        return HTTP_UNAUTHORIZED;
    }

    while (*auth_line == ' ' || *auth_line == '\t') {
