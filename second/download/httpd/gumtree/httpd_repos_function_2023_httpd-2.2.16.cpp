static void *create_authz_host_dir_config(apr_pool_t *p, char *dummy)
{
    int i;
    authz_host_dir_conf *conf =
        (authz_host_dir_conf *)apr_pcalloc(p, sizeof(authz_host_dir_conf));

    for (i = 0; i < METHODS; ++i) {
        conf->order[i] = DENY_THEN_ALLOW;
    }
    conf->allows = apr_array_make(p, 1, sizeof(allowdeny));
    conf->denys = apr_array_make(p, 1, sizeof(allowdeny));

    return (void *)conf;
}