static void pool_destroy_debug(apr_pool_t *pool, const char *file_line)
{
    apr_pool_check_integrity(pool);

#if (APR_POOL_DEBUG & APR_POOL_DEBUG_VERBOSE)
    apr_pool_log_event(pool, "DESTROY", file_line, 1);
#endif /* (APR_POOL_DEBUG & APR_POOL_DEBUG_VERBOSE) */

    pool_clear_debug(pool, file_line);

    /* Remove the pool from the parents child list */
    if (pool->parent) {
#if APR_HAS_THREADS
        apr_thread_mutex_t *mutex;

        if ((mutex = pool->parent->mutex) != NULL)
            apr_thread_mutex_lock(mutex);
#endif /* APR_HAS_THREADS */

        if ((*pool->ref = pool->sibling) != NULL)
            pool->sibling->ref = pool->ref;

#if APR_HAS_THREADS
        if (mutex)
            apr_thread_mutex_unlock(mutex);
#endif /* APR_HAS_THREADS */
    }

    if (pool->allocator != NULL
        && apr_allocator_owner_get(pool->allocator) == pool) {
        apr_allocator_destroy(pool->allocator);
    }

    /* Free the pool itself */
    free(pool);
}