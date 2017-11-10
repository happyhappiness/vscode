static const char *authn_ap_auth_name(request_rec *r)
{
    authn_core_dir_conf *conf;

    conf = (authn_core_dir_conf *)ap_get_module_config(r->per_dir_config,
        &authn_core_module);

    return apr_pstrdup(r->pool, conf->ap_auth_name);
}