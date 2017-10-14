static authz_status group_check_authorization(request_rec *r,
                                              const char *require_args,
                                              const void *parsed_require_args)
{
    authz_groupfile_config_rec *conf = ap_get_module_config(r->per_dir_config,
            &authz_groupfile_module);
    char *user = r->user;

    const char *err = NULL;
    const ap_expr_info_t *expr = parsed_require_args;
    const char *require;

    const char *t, *w;
    apr_table_t *grpstatus = NULL;
    apr_status_t status;

    if (!user) {
        return AUTHZ_DENIED_NO_USER;
    }

    /* If there is no group file - then we are not
     * configured. So decline.
     */
    if (!(conf->groupfile)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01664)
                        "No group file was specified in the configuration");
        return AUTHZ_DENIED;
    }

    status = groups_for_user(r->pool, user, conf->groupfile,
                                &grpstatus);

    if (status != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(01665)
                        "Could not open group file: %s",
                        conf->groupfile);
        return AUTHZ_DENIED;
    }

    if (apr_is_empty_table(grpstatus)) {
        /* no groups available, so exit immediately */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01666)
                      "Authorization of user %s to access %s failed, reason: "
                      "user doesn't appear in group file (%s).",
                      r->user, r->uri, conf->groupfile);
        return AUTHZ_DENIED;
    }

    require = ap_expr_str_exec(r, expr, &err);
    if (err) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02592)
                      "authz_groupfile authorize: require group: Can't "
                      "evaluate require expression: %s", err);
        return AUTHZ_DENIED;
    }

    t = require;
    while ((w = ap_getword_conf(r->pool, &t)) && w[0]) {
        if (apr_table_get(grpstatus, w)) {
            return AUTHZ_GRANTED;
        }
    }

    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01667)
                    "Authorization of user %s to access %s failed, reason: "
                    "user is not part of the 'require'ed group(s).",
                    r->user, r->uri);

    return AUTHZ_DENIED;
}