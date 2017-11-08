static int apr_pool_walk_tree(apr_pool_t *pool,
                              int (*fn)(apr_pool_t *pool, void *data),
                              void *data)
{
    int rv;
    apr_pool_t *child;

    rv = fn(pool, data);
    if (rv)
        return rv;

#if APR_HAS_THREADS
    if (pool->mutex) {
        apr_thread_mutex_lock(pool->mutex);
                        }
#endif /* APR_HAS_THREADS */

    child = pool->child;
    while (child) {
        rv = apr_pool_walk_tree(child, fn, data);
        if (rv)
            break;

        child = child->sibling;
    }

#if APR_HAS_THREADS
    if (pool->mutex) {
        apr_thread_mutex_unlock(pool->mutex);
    }
#endif /* APR_HAS_THREADS */

    return rv;
}