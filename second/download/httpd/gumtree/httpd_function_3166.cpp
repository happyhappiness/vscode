static authn_status get_dbm_realm_hash(request_rec *r, const char *user,
                                       const char *realm, char **rethash)
{
    authn_dbm_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                      &authn_dbm_module);
    apr_status_t rv;
    char *dbm_hash;
    char *colon_hash;

    rv = fetch_dbm_value(conf->dbmtype, conf->pwfile,
                         apr_pstrcat(r->pool, user, ":", realm, NULL),
                         &dbm_hash, r->pool);

    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "Could not open dbm (type %s) hash file: %s",
                      conf->dbmtype, conf->pwfile);
        return AUTH_GENERAL_ERROR;
    }

    if (!dbm_hash) {
        return AUTH_USER_NOT_FOUND;
    }

    colon_hash = ap_strchr(dbm_hash, ':');
    if (colon_hash) {
        *colon_hash = '\0';
    }

    *rethash = dbm_hash;
    AUTHN_CACHE_STORE(r, user, realm, dbm_hash);

    return AUTH_USER_FOUND;
}