static authz_status dbdgroup_check_authorization(request_rec *r,
                                                 const char *require_args,
                                                 const void *parsed_require_args)
{
    int i, rv;
    const char *w;
    apr_array_header_t *groups = NULL;

    const char *err = NULL;
    const ap_expr_info_t *expr = parsed_require_args;
    const char *require;

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
            return AUTHZ_GENERAL_ERROR;
        }
    }

    require = ap_expr_str_exec(r, expr, &err);
    if (err) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02590)
                      "authz_dbd authorize: require dbd-group: Can't "
                      "evaluate require expression: %s", err);
        return AUTHZ_DENIED;
    }

    t = require;
    while (t[0]) {
        w = ap_getword_white(r->pool, &t);
        for (i=0; i < groups->nelts; ++i) {
            if (!strcmp(w, ((const char**)groups->elts)[i])) {
                return AUTHZ_GRANTED;
            }
        }
    }

    return AUTHZ_DENIED;
}