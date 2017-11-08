static cache *init_cache(apr_pool_t *p)
{
    cache *c;

    c = (cache *)apr_palloc(p, sizeof(cache));
    if (apr_pool_create(&c->pool, p) != APR_SUCCESS) {
        return NULL;
    }
    c->lists = apr_array_make(c->pool, 2, sizeof(cachelist));
#if APR_HAS_THREADS
    (void)apr_thread_mutex_create(&(c->lock), APR_THREAD_MUTEX_DEFAULT, p);
#endif
    return c;
}