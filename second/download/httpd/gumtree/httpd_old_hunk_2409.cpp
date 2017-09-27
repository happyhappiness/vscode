        if (!(conf->authoritative) && auth_result != AUTH_DENIED) {
            return DECLINED;
        }

        switch (auth_result) {
        case AUTH_DENIED:
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, LOG_PREFIX
                          "user '%s': authentication failure for \"%s\": "
                          "password Mismatch",
                          sent_user, r->uri);
            return_code = HTTP_UNAUTHORIZED;
            break;
        case AUTH_USER_NOT_FOUND:
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, LOG_PREFIX
                          "user '%s' not found: %s", sent_user, r->uri);
            return_code = HTTP_UNAUTHORIZED;
            break;
        case AUTH_GENERAL_ERROR:
        default:
            /*
