void *h2_config_merge_svr(apr_pool_t *pool, void *basev, void *addv)
{
    return h2_config_merge(pool, basev, addv);
}