static void *create_magic_server_config(apr_pool_t *p, server_rec *d)
{
    /* allocate the config - use pcalloc because it needs to be zeroed */
    return apr_pcalloc(p, sizeof(magic_server_config_rec));
}