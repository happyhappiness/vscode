static const dav_provider *dav_get_provider(request_rec *r)
{
    dav_dir_conf *conf;

    conf = ap_get_module_config(r->per_dir_config, &dav_module);
    /* assert: conf->provider_name != NULL
       (otherwise, DAV is disabled, and we wouldn't be here) */

    /* assert: conf->provider != NULL
       (checked when conf->provider_name is set) */
    return conf->provider;
}