static void *create_authz_core_dir_config(apr_pool_t *p, char *dummy)
{
    authz_core_dir_conf *conf = apr_pcalloc(p, sizeof(*conf));

    conf->op = AUTHZ_LOGIC_OFF;

    conf->next = authz_core_first_dir_conf;
    authz_core_first_dir_conf = conf;

    return (void *)conf;
}