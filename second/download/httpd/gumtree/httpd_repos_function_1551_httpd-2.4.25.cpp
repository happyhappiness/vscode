static int init_cache(apr_pool_t *p)
{
    cachep = apr_palloc(p, sizeof(cache));
    if (apr_pool_create(&cachep->pool, p) != APR_SUCCESS) {
        cachep = NULL; /* turns off cache */
        return 0;
    }

    cachep->maps = apr_hash_make(cachep->pool);
#if APR_HAS_THREADS
    (void)apr_thread_mutex_create(&(cachep->lock), APR_THREAD_MUTEX_DEFAULT, p);
#endif

    return 1;
}