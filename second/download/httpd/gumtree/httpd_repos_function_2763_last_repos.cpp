static int pool_register(h2_bucket_beam *beam, apr_pool_t *pool, 
                         apr_status_t (*cleanup)(void *))
{
    if (pool && pool != beam->pool) {
        apr_pool_pre_cleanup_register(pool, beam, cleanup);
        return 1;
    }
    return 0;
}