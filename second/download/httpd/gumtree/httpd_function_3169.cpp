static authn_status get_realm_hash(request_rec *r, const char *user,
                                   const char *realm, char **rethash)
{
    authn_file_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                       &authn_file_module);
    ap_configfile_t *f;
    char l[MAX_STRING_LEN];
    apr_status_t status;
    char *file_hash = NULL;

    status = ap_pcfg_openfile(&f, r->pool, conf->pwfile);

    if (status != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                      "Could not open password file: %s", conf->pwfile);
        return AUTH_GENERAL_ERROR;
    }

    while (!(ap_cfg_getline(l, MAX_STRING_LEN, f))) {
        const char *rpw, *w, *x;

        /* Skip # or blank lines. */
        if ((l[0] == '#') || (!l[0])) {
            continue;
        }

        rpw = l;
        w = ap_getword(r->pool, &rpw, ':');
        x = ap_getword(r->pool, &rpw, ':');

        if (x && w && !strcmp(user, w) && !strcmp(realm, x)) {
            /* Remember that this is a md5 hash of user:realm:password.  */
            file_hash = ap_getword(r->pool, &rpw, ':');
            break;
        }
    }
    ap_cfg_closefile(f);

    if (!file_hash) {
        return AUTH_USER_NOT_FOUND;
    }

    *rethash = file_hash;
    AUTHN_CACHE_STORE(r, user, realm, file_hash);

    return AUTH_USER_FOUND;
}