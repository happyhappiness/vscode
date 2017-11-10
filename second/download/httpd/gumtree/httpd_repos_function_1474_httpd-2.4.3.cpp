static void *create_mconfig_for_server(apr_pool_t *p, server_rec *s)
{
    return mkconfig(p);
}