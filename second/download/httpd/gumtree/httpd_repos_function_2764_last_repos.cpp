static int pool_kill(h2_bucket_beam *beam, apr_pool_t *pool,
                     apr_status_t (*cleanup)(void *)) {
    if (pool && pool != beam->pool) {
        apr_pool_cleanup_kill(pool, beam, cleanup);
        return 1;
    }
    return 0;
}