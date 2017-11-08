static int authenticate_basic_user(request_rec *r)
{
    auth_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                 &auth_module);
    const char *sent_pw;
    char *real_pw;
    apr_status_t invalid_pw;
    int res;

    if ((res = ap_get_basic_auth_pw(r, &sent_pw))) {
        return res;
    }

    if (!conf->auth_pwfile) {
        return DECLINED;
    }

    if (!(real_pw = get_pw(r, r->user, conf->auth_pwfile))) {
        if (!(conf->auth_authoritative)) {
            return DECLINED;
        }
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "user %s not found: %s", r->user, r->uri);
        ap_note_basic_auth_failure(r);
        return HTTP_UNAUTHORIZED;
    }
    invalid_pw = apr_password_validate(sent_pw, real_pw);
    if (invalid_pw != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "user %s: authentication failure for \"%s\": "
                      "Password Mismatch",
                      r->user, r->uri);
        ap_note_basic_auth_failure(r);
        return HTTP_UNAUTHORIZED;
    }
    return OK;
}