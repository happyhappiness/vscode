static void *create_sed_dir_config(apr_pool_t *p, char *s)
{
    sed_config *cfg = apr_pcalloc(p, sizeof(sed_config));
    return cfg;
}