static authn_status check_password(request_rec *r, const char *user,
                                   const char *password)
{
    authn_file_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                       &authn_file_module);
    ap_configfile_t *f;
    char l[MAX_STRING_LEN];
    apr_status_t status;
    char *file_password = NULL;

    status = ap_pcfg_openfile(&f, r->pool, conf->pwfile);

    if (status != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                      "Could not open password file: %s", conf->pwfile);
        return AUTH_GENERAL_ERROR;
    }

    while (!(ap_cfg_getline(l, MAX_STRING_LEN, f))) {
        const char *rpw, *w;

        /* Skip # or blank lines. */
        if ((l[0] == '#') || (!l[0])) {
            continue;
        }

        rpw = l;
        w = ap_getword(r->pool, &rpw, ':');

        if (!strcmp(user, w)) {
            file_password = ap_getword(r->pool, &rpw, ':');
            break;
        }
    }
    ap_cfg_closefile(f);

    if (!file_password) {
        return AUTH_USER_NOT_FOUND;
    }
    AUTHN_CACHE_STORE(r, user, NULL, file_password);

    status = apr_password_validate(password, file_password);
    if (status != APR_SUCCESS) {
        return AUTH_DENIED;
    }

    return AUTH_GRANTED;
}