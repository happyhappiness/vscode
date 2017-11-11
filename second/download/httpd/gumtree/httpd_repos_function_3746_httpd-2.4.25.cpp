static void *create_access_compat_dir_config(apr_pool_t *p, char *dummy)
{
    int i;
    access_compat_dir_conf *conf =
        (access_compat_dir_conf *)apr_pcalloc(p, sizeof(access_compat_dir_conf));

    for (i = 0; i < METHODS; ++i) {
        conf->order[i] = DENY_THEN_ALLOW;
    }
    conf->allows = apr_array_make(p, 1, sizeof(allowdeny));
    conf->denys = apr_array_make(p, 1, sizeof(allowdeny));
    conf->satisfy = apr_palloc(p, sizeof(*conf->satisfy) * METHODS);
    for (i = 0; i < METHODS; ++i) {
        conf->satisfy[i] = SATISFY_NOSPEC;
    }

    return (void *)conf;
}