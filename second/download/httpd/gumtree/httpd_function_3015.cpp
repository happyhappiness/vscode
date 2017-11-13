static authz_status dbdlogout_check_authorization(request_rec *r,
                                              const char *require_args)
{
    authz_dbd_cfg *cfg = ap_get_module_config(r->per_dir_config,
                                              &authz_dbd_module);

    if (!r->user) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
            "access to %s failed, reason: no authenticated user", r->uri);
        return AUTHZ_DENIED;
    }

    return (authz_dbd_login(r, cfg, "logout") == OK ? AUTHZ_GRANTED : AUTHZ_DENIED);
}