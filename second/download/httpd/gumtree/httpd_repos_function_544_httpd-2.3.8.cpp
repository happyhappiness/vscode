static void *create_setenvif_config_svr(apr_pool_t *p, server_rec *dummy)
{
    return create_setenvif_config(p);
}