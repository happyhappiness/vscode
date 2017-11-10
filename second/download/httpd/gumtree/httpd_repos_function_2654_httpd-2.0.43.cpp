static void pool_bucket_destroy(void *data)
{
    apr_bucket_pool *p = data;

    /* If the pool is cleaned up before the last reference goes
     * away, the data is really now on the heap; heap_destroy() takes
     * over.  free() in heap_destroy() thinks it's freeing
     * an apr_bucket_heap, when in reality it's freeing the whole
     * apr_bucket_pool for us.
     */
    if (p->pool) {
        /* the shared resource is still in the pool
         * because the pool has not been cleaned up yet
         */
        if (apr_bucket_shared_destroy(p)) {
            apr_pool_cleanup_kill(p->pool, p, pool_bucket_cleanup);
            apr_bucket_free(p);
        }
    }
    else {
        /* the shared resource is no longer in the pool, it's
         * on the heap, but this reference still thinks it's a pool
         * bucket.  we should just go ahead and pass control to
         * heap_destroy() for it since it doesn't know any better.
         */
        apr_bucket_type_heap.destroy(p);
    }
}