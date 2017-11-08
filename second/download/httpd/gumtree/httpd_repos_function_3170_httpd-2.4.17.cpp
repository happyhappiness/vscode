static authz_status dbmgroup_check_authorization(request_rec *r,
                                                 const char *require_args,
                                                 const void *parsed_require_args)
{
    authz_dbm_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                      &authz_dbm_module);
    char *user = r->user;

    const char *err = NULL;
    const ap_expr_info_t *expr = parsed_require_args;
    const char *require;

    const char *t;
    char *w;
    const char *orig_groups = NULL;
    const char *realm = ap_auth_name(r);
    const char *groups;
    char *v;

    if (!user) {
        return AUTHZ_DENIED_NO_USER;
    }

    if (!conf->grpfile) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01798)
                        "No group file was specified in the configuration");
        return AUTHZ_DENIED;
    }

    /* fetch group data from dbm file only once. */
    if (!orig_groups) {
        apr_status_t status;

        status = get_dbm_grp(r, apr_pstrcat(r->pool, user, ":", realm, NULL),
                             user, conf->grpfile, conf->dbmtype, &groups);

        if (status != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(01799)
                          "could not open dbm (type %s) group access "
                          "file: %s", conf->dbmtype, conf->grpfile);
            return AUTHZ_GENERAL_ERROR;
        }

        if (groups == NULL) {
            /* no groups available, so exit immediately */
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01800)
                          "Authorization of user %s to access %s failed, reason: "
                          "user doesn't appear in DBM group file (%s).",
                          r->user, r->uri, conf->grpfile);
            return AUTHZ_DENIED;
        }

        orig_groups = groups;
    }

    require = ap_expr_str_exec(r, expr, &err);
    if (err) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02591)
                      "authz_dbm authorize: require dbm-group: Can't "
                      "evaluate require expression: %s", err);
        return AUTHZ_DENIED;
    }

    t = require;
    while ((w = ap_getword_white(r->pool, &t)) && w[0]) {
        groups = orig_groups;
        while (groups[0]) {
            v = ap_getword(r->pool, &groups, ',');
            if (!strcmp(v, w)) {
                return AUTHZ_GRANTED;
            }
        }
    }

    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01801)
                  "Authorization of user %s to access %s failed, reason: "
                  "user is not part of the 'require'ed group(s).",
                  r->user, r->uri);

    return AUTHZ_DENIED;
}