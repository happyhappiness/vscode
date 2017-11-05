static authz_status filegroup_check_authorization(request_rec *r,
                                              const char *require_args)
{
    authz_groupfile_config_rec *conf = ap_get_module_config(r->per_dir_config,
            &authz_groupfile_module);
    char *user = r->user;
    apr_table_t *grpstatus = NULL;
    apr_status_t status;
    const char *filegroup = NULL;

    if (!user) {
        return AUTHZ_DENIED_NO_USER;
    }

    /* If there is no group file - then we are not
     * configured. So decline.
     */
    if (!(conf->groupfile)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                        "No group file was specified in the configuration");
        return AUTHZ_DENIED;
    }

    status = groups_for_user(r->pool, user, conf->groupfile,
                             &grpstatus);
    if (status != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                      "Could not open group file: %s",
                      conf->groupfile);
        return AUTHZ_DENIED;
    }

    if (apr_table_elts(grpstatus)->nelts == 0) {
        /* no groups available, so exit immediately */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                        "Authorization of user %s to access %s failed, reason: "
                        "user doesn't appear in group file (%s).",
                        r->user, r->uri, conf->groupfile);
        return AUTHZ_DENIED;
    }

    filegroup = authz_owner_get_file_group(r);

    if (filegroup) {
        if (apr_table_get(grpstatus, filegroup)) {
            return AUTHZ_GRANTED;
        }
    }
    else {
        /* No need to emit a error log entry because the call
        to authz_owner_get_file_group already did it
        for us.
        */
        return AUTHZ_DENIED;
    }

    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                  "Authorization of user %s to access %s failed, reason: "
                  "user is not part of the 'require'ed file group.",
                  r->user, r->uri);

    return AUTHZ_DENIED;
}