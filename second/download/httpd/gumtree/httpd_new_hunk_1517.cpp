        *out = val;
    }

    return retval;
}

static authz_status dbmgroup_check_authorization(request_rec *r,
                                             const char *require_args)
{
    authz_dbm_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                      &authz_dbm_module);
    char *user = r->user;
    const char *t;
    char *w;
    const char *orig_groups = NULL;
    const char *realm = ap_auth_name(r);
    const char *groups;
    char *v;

    if (!user) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
            "access to %s failed, reason: no authenticated user", r->uri);
        return AUTHZ_DENIED;
    }

    if (!conf->grpfile) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                        "No group file was specified in the configuration");
        return AUTHZ_DENIED;
    }

    /* fetch group data from dbm file only once. */
    if (!orig_groups) {
        apr_status_t status;

        status = get_dbm_grp(r, apr_pstrcat(r->pool, user, ":", realm, NULL),
                             user, conf->grpfile, conf->dbmtype, &groups);

        if (status != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                          "could not open dbm (type %s) group access "
                          "file: %s", conf->dbmtype, conf->grpfile);
            return AUTHZ_GENERAL_ERROR;
        }

        if (groups == NULL) {
            /* no groups available, so exit immediately */
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Authorization of user %s to access %s failed, reason: "
                          "user doesn't appear in DBM group file (%s).", 
                          r->user, r->uri, conf->grpfile);
            return AUTHZ_DENIED;
        }

        orig_groups = groups;
    }

    t = require_args;
    while ((w = ap_getword_white(r->pool, &t)) && w[0]) {
        groups = orig_groups;
        while (groups[0]) {
            v = ap_getword(r->pool, &groups, ',');
            if (!strcmp(v, w)) {
                return AUTHZ_GRANTED;
            }
        }
    }

    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                  "Authorization of user %s to access %s failed, reason: "
                  "user is not part of the 'require'ed group(s).",
                  r->user, r->uri);

    return AUTHZ_DENIED;
}

APR_OPTIONAL_FN_TYPE(authz_owner_get_file_group) *authz_owner_get_file_group;

static authz_status dbmfilegroup_check_authorization(request_rec *r,
                                              const char *require_args)
{
    authz_dbm_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                      &authz_dbm_module);
    char *user = r->user;
    const char *realm = ap_auth_name(r);
    const char *filegroup = NULL;
    const char *orig_groups = NULL;
    apr_status_t status;
    const char *groups;
    char *v;

    if (!user) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
            "access to %s failed, reason: no authenticated user", r->uri);
        return AUTHZ_DENIED;
    }

    if (!conf->grpfile) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                        "No group file was specified in the configuration");
        return AUTHZ_DENIED;
    }

    /* fetch group data from dbm file. */
    status = get_dbm_grp(r, apr_pstrcat(r->pool, user, ":", realm, NULL),
                         user, conf->grpfile, conf->dbmtype, &groups);

    if (status != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                      "could not open dbm (type %s) group access "
                      "file: %s", conf->dbmtype, conf->grpfile);
        return AUTHZ_DENIED;
    }

    if (groups == NULL) {
        /* no groups available, so exit immediately */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Authorization of user %s to access %s failed, reason: "
                      "user doesn't appear in DBM group file (%s).", 
                      r->user, r->uri, conf->grpfile);
        return AUTHZ_DENIED;
    }

    orig_groups = groups;

    filegroup = authz_owner_get_file_group(r);

    if (filegroup) {
        groups = orig_groups;
        while (groups[0]) {
            v = ap_getword(r->pool, &groups, ',');
            if (!strcmp(v, filegroup)) {
                return AUTHZ_GRANTED;
            }
        }
    }

    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                  "Authorization of user %s to access %s failed, reason: "
                  "user is not part of the 'require'ed group(s).",
                  r->user, r->uri);

    return AUTHZ_DENIED;
}

static const authz_provider authz_dbmgroup_provider =
{
    &dbmgroup_check_authorization,
};

static const authz_provider authz_dbmfilegroup_provider =
{
    &dbmfilegroup_check_authorization,
};


static void register_hooks(apr_pool_t *p)
{
    authz_owner_get_file_group = APR_RETRIEVE_OPTIONAL_FN(authz_owner_get_file_group);

    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "dbm-group",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_dbmgroup_provider,
                              AP_AUTH_INTERNAL_PER_CONF);
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "dbm-file-group",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_dbmfilegroup_provider,
                              AP_AUTH_INTERNAL_PER_CONF);
}

AP_DECLARE_MODULE(authz_dbm) =
{
    STANDARD20_MODULE_STUFF,
    create_authz_dbm_dir_config, /* dir config creater */
    NULL,                        /* dir merger --- default is to override */
    NULL,                        /* server config */
    NULL,                        /* merge server config */
