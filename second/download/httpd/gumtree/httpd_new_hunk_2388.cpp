        return DECLINED;
    }

    /* We need an authentication realm. */
    if (!ap_auth_name(r)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR,
                      0, r, APLOGNO(01615) "need AuthName: %s", r->uri);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    r->ap_auth_type = (char*)current_auth;

    res = get_basic_auth(r, &sent_user, &sent_pw);
