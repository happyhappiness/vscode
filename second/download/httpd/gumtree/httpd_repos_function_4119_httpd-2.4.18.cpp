apr_status_t ap_queue_info_wait_for_idler(fd_queue_info_t *queue_info,
                                          apr_pool_t **recycled_pool)
{
    apr_status_t rv;

    *recycled_pool = NULL;

    /* Block if the count of idle workers is zero */
    if (queue_info->idlers == 0) {
        rv = apr_thread_mutex_lock(queue_info->idlers_mutex);
        if (rv != APR_SUCCESS) {
            return rv;
        }
        /* Re-check the idle worker count to guard against a
         * race condition.  Now that we're in the mutex-protected
         * region, one of two things may have happened:
         *   - If the idle worker count is still zero, the
         *     workers are all still busy, so it's safe to
         *     block on a condition variable, BUT
         *     we need to check for idle worker count again
         *     when we are signaled since it can happen that
         *     we are signaled by a worker thread that went idle
         *     but received a context switch before it could
         *     tell us. If it does signal us later once it is on
         *     CPU again there might be no idle worker left.
         *     See
         *     https://issues.apache.org/bugzilla/show_bug.cgi?id=45605#c4
         *   - If the idle worker count is nonzero, then a
         *     worker has become idle since the first check
         *     of queue_info->idlers above.  It's possible
         *     that the worker has also signaled the condition
         *     variable--and if so, the listener missed it
         *     because it wasn't yet blocked on the condition
         *     variable.  But if the idle worker count is
         *     now nonzero, it's safe for this function to
         *     return immediately.
         */
        while (queue_info->idlers == 0) {
            rv = apr_thread_cond_wait(queue_info->wait_for_idler,
                                  queue_info->idlers_mutex);
            if (rv != APR_SUCCESS) {
                apr_status_t rv2;
                rv2 = apr_thread_mutex_unlock(queue_info->idlers_mutex);
                if (rv2 != APR_SUCCESS) {
                    return rv2;
                }
                return rv;
            }
        }
        rv = apr_thread_mutex_unlock(queue_info->idlers_mutex);
        if (rv != APR_SUCCESS) {
            return rv;
        }
    }

    /* Atomically decrement the idle worker count */
    apr_atomic_dec32(&(queue_info->idlers));

    /* Atomically pop a pool from the recycled list */

    /* This function is safe only as long as it is single threaded because
     * it reaches into the queue and accesses "next" which can change.
     * We are OK today because it is only called from the listener thread.
     * cas-based pushes do not have the same limitation - any number can
     * happen concurrently with a single cas-based pop.
     */

    for (;;) {
        struct recycled_pool *first_pool = queue_info->recycled_pools;
        if (first_pool == NULL) {
            break;
        }
        if (apr_atomic_casptr((void*)&(queue_info->recycled_pools), first_pool->next,
                              first_pool) == first_pool) {
            *recycled_pool = first_pool->pool;
            break;
        }
    }

    if (queue_info->terminated) {
        return APR_EOF;
    }
    else {
        return APR_SUCCESS;
    }
}