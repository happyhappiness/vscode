    apr_array_header_t *groups = NULL;
    const char *t;
    authz_dbd_cfg *cfg = ap_get_module_config(r->per_dir_config,
                                              &authz_dbd_module);

    if (!r->user) {
        return AUTHZ_DENIED_NO_USER;
    }

    if (groups == NULL) {
        groups = apr_array_make(r->pool, 4, sizeof(const char*));
        rv = authz_dbd_group_query(r, cfg, groups);
        if (rv != OK) {
