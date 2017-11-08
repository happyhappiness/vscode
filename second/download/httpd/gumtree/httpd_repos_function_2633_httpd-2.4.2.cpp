static int authz_some_auth_required(request_rec *r)
{
    authz_core_dir_conf *conf;

    conf = ap_get_module_config(r->per_dir_config, &authz_core_module);

    if (conf->section
        && (conf->section->limited & (AP_METHOD_BIT << r->method_number))) {
        return 1;
    }

    return 0;
}