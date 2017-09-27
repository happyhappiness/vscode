    apr_array_header_t *groups = NULL;
    const char *t;
    authz_dbd_cfg *cfg = ap_get_module_config(r->per_dir_config,
                                              &authz_dbd_module);

    if (!r->user) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
            "access to %s failed, reason: no authenticated user", r->uri);
        return AUTHZ_DENIED;
    }

    if (groups == NULL) {
        groups = apr_array_make(r->pool, 4, sizeof(const char*));
        rv = authz_dbd_group_query(r, cfg, groups);
        if (rv != OK) {
