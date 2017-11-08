static int dbm_authenticate_basic_user(request_rec *r)
{
    dbm_auth_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                     &auth_dbm_module);
    const char *sent_pw;
    char *real_pw, *colon_pw;
    apr_status_t invalid_pw;
    int res;

    if ((res = ap_get_basic_auth_pw(r, &sent_pw)))
        return res;

    if (!conf->auth_dbmpwfile)
        return DECLINED;

    if (!(real_pw = get_dbm_pw(r, r->user, conf->auth_dbmpwfile,
                               conf->auth_dbmtype))) {
        if (!(conf->auth_dbmauthoritative))
            return DECLINED;
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
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
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "DBM user %s: authentication failure for \"%s\": "
                      "Password Mismatch",
                      r->user, r->uri);
        ap_note_basic_auth_failure(r);
        return HTTP_UNAUTHORIZED;
    }
    return OK;
}