static authn_status check_dbm_pw(request_rec *r, const char *user,
                                 const char *password)
{
    authn_dbm_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                      &authn_dbm_module);
    apr_status_t rv;
    char *dbm_password;
    char *colon_pw;

    rv = fetch_dbm_value(conf->dbmtype, conf->pwfile, user, &dbm_password,
                         r->pool);

    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "could not open dbm (type %s) auth file: %s",
                      conf->dbmtype, conf->pwfile);
        return AUTH_GENERAL_ERROR;
    }

    if (!dbm_password) {
        return AUTH_USER_NOT_FOUND;
    }

    colon_pw = ap_strchr(dbm_password, ':');
    if (colon_pw) {
        *colon_pw = '\0';
    }
    AUTHN_CACHE_STORE(r, user, NULL, dbm_password);

    rv = apr_password_validate(password, dbm_password);

    if (rv != APR_SUCCESS) {
        return AUTH_DENIED;
    }

    return AUTH_GRANTED;
}