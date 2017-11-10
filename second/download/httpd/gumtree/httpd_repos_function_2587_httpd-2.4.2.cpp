static void *create_authn_core_dir_config(apr_pool_t *p, char *dummy)
{
    authn_core_dir_conf *conf =
            (authn_core_dir_conf *)apr_pcalloc(p, sizeof(authn_core_dir_conf));

    return (void *)conf;
}