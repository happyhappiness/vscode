static void apr_pool_check_integrity(apr_pool_t *pool)
{
    /* Rule of thumb: use of the global pool is always
     * ok, since the only user is apr_pools.c.  Unless
     * people have searched for the top level parent and
     * started to use that...
     */
    if (pool == global_pool || global_pool == NULL)
        return;

    /* Lifetime
     * This basically checks to see if the pool being used is still
     * a relative to the global pool.  If not it was previously
     * destroyed, in which case we abort().
     */
#if (APR_POOL_DEBUG & APR_POOL_DEBUG_LIFETIME)
    if (!apr_pool_is_child_of(pool, global_pool)) {
#if (APR_POOL_DEBUG & APR_POOL_DEBUG_VERBOSE_ALL)
        apr_pool_log_event(pool, "LIFE",
                           __FILE__ ":apr_pool_integrity check", 0);
#endif /* (APR_POOL_DEBUG & APR_POOL_DEBUG_VERBOSE_ALL) */
        abort();
    }
#endif /* (APR_POOL_DEBUG & APR_POOL_DEBUG_LIFETIME) */

#if (APR_POOL_DEBUG & APR_POOL_DEBUG_OWNER)
#if APR_HAS_THREADS
    if (!apr_os_thread_equal(pool->owner, apr_os_thread_current())) {
#if (APR_POOL_DEBUG & APR_POOL_DEBUG_VERBOSE_ALL)
        apr_pool_log_event(pool, "THREAD",
                           __FILE__ ":apr_pool_integrity check", 0);
#endif /* (APR_POOL_DEBUG & APR_POOL_DEBUG_VERBOSE_ALL) */
        abort();
    }
#endif /* APR_HAS_THREADS */
#endif /* (APR_POOL_DEBUG & APR_POOL_DEBUG_OWNER) */
}