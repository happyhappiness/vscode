static void *create_reflector_dir_config(apr_pool_t * p, char *d)
{
    reflector_cfg *conf = apr_pcalloc(p, sizeof(reflector_cfg));

    conf->headers = apr_table_make(p, 8);

    return conf;
}