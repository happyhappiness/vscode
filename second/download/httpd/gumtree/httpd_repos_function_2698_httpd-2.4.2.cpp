static authz_status dbdlogin_check_authorization(request_rec *r,
                                                 const char *require_args,
                                                 const void *parsed_require_args)
{
    authz_dbd_cfg *cfg = ap_get_module_config(r->per_dir_config,
                                              &authz_dbd_module);

    if (!r->user) {
        return AUTHZ_DENIED_NO_USER;
    }

    return (authz_dbd_login(r, cfg, "login") == OK ? AUTHZ_GRANTED : AUTHZ_DENIED);
}