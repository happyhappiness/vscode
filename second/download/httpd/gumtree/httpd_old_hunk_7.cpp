        return DECLINED;

    if (!(real_pw = get_dbm_pw(r, r->user, conf->auth_dbmpwfile,
                               conf->auth_dbmtype))) {
        if (!(conf->auth_dbmauthoritative))
            return DECLINED;
        ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                      "DBM user %s not found: %s", r->user, r->filename);
        ap_note_basic_auth_failure(r);
        return HTTP_UNAUTHORIZED;
    }
    /* Password is up to first : if exists */
    colon_pw = strchr(real_pw, ':');
    if (colon_pw) {
        *colon_pw = '\0';
    }
    invalid_pw = apr_password_validate(sent_pw, real_pw);
    if (invalid_pw != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                      "DBM user %s: authentication failure for \"%s\": "
                      "Password Mismatch",
                      r->user, r->uri);
        ap_note_basic_auth_failure(r);
        return HTTP_UNAUTHORIZED;
    }
