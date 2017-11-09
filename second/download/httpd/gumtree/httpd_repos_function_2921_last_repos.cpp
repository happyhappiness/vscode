void *h2_config_create_svr(apr_pool_t *pool, server_rec *s)
{
    return h2_config_create(pool, "srv", s->defn_name);
}