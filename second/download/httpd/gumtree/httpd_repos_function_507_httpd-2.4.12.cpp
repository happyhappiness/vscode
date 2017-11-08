static void *create_env_dir_config(apr_pool_t *p, char *dummy)
{
    env_dir_config_rec *conf = apr_palloc(p, sizeof(*conf));

    conf->vars = apr_table_make(p, 10);
    conf->unsetenv = apr_table_make(p, 10);

    return conf;
}