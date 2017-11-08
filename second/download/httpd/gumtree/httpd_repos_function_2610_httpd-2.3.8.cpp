static void *create_authz_host_dir_config(apr_pool_t *p, char *dummy)
{
    authz_host_dir_conf *conf =
        (authz_host_dir_conf *)apr_pcalloc(p, sizeof(authz_host_dir_conf));

    return (void *)conf;
}