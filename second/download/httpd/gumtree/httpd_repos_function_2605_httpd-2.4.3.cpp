static void *merge_authn_core_dir_config(apr_pool_t *a, void *basev, void *newv)
{
    authn_core_dir_conf *base = (authn_core_dir_conf *)basev;
    authn_core_dir_conf *new = (authn_core_dir_conf *)newv;
    authn_core_dir_conf *conf =
        (authn_core_dir_conf *)apr_pcalloc(a, sizeof(authn_core_dir_conf));

    if (new->auth_type_set) {
        conf->ap_auth_type = new->ap_auth_type;
        conf->auth_type_set = 1;
    }
    else {
        conf->ap_auth_type = base->ap_auth_type;
        conf->auth_type_set = base->auth_type_set;
    }

    if (new->ap_auth_name) {
        conf->ap_auth_name = new->ap_auth_name;
    } else {
        conf->ap_auth_name = base->ap_auth_name;
    }

    return (void*)conf;
}