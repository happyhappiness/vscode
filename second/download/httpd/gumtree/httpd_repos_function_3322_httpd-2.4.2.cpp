apr_status_t ap_queue_info_wait_for_idler(fd_queue_info_t * queue_info,
                                          int *had_to_block)
{
    apr_status_t rv;
    int prev_idlers;

    /* Atomically decrement the idle worker count, saving the old value */
    /* See TODO in ap_queue_info_set_idle() */
    prev_idlers = apr_atomic_add32((apr_uint32_t *)&(queue_info->idlers), -1);

    /* Block if there weren't any idle workers */
    if (prev_idlers <= 0) {
        rv = apr_thread_mutex_lock(queue_info->idlers_mutex);
        if (rv != APR_SUCCESS) {
            AP_DEBUG_ASSERT(0);
            /* See TODO in ap_queue_info_set_idle() */
            apr_atomic_inc32((apr_uint32_t *)&(queue_info->idlers));    /* back out dec */
            return rv;
        }
        /* Re-check the idle worker count to guard against a
         * race condition.  Now that we're in the mutex-protected
         * region, one of two things may have happened:
         *   - If the idle worker count is still negative, the
         *     workers are all still busy, so it's safe to
         *     block on a condition variable.
         *   - If the idle worker count is non-negative, then a
         *     worker has become idle since the first check
         *     of queue_info->idlers above.  It's possible
         *     that the worker has also signaled the condition
         *     variable--and if so, the listener missed it
         *     because it wasn't yet blocked on the condition
         *     variable.  But if the idle worker count is
         *     now non-negative, it's safe for this function to
         *     return immediately.
         *
         *     A negative value in queue_info->idlers tells how many
         *     threads are waiting on an idle worker.
         */
        if (queue_info->idlers < 0) {
            *had_to_block = 1;
            rv = apr_thread_cond_wait(queue_info->wait_for_idler,
                                      queue_info->idlers_mutex);
            if (rv != APR_SUCCESS) {
                apr_status_t rv2;
                AP_DEBUG_ASSERT(0);
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

    if (queue_info->terminated) {
        return APR_EOF;
    }
    else {
        return APR_SUCCESS;
    }
}