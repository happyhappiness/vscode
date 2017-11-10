apr_status_t ap_queue_info_set_idle(fd_queue_info_t * queue_info,
                                    apr_pool_t * pool_to_recycle)
{
    apr_status_t rv;
    int prev_idlers;

    ap_push_pool(queue_info, pool_to_recycle);

    /* Atomically increment the count of idle workers */
    /*
     * TODO: The atomics expect unsigned whereas we're using signed.
     *       Need to double check that they work as expected or else
     *       rework how we determine blocked.
     */
    prev_idlers = apr_atomic_inc32((apr_uint32_t *)&(queue_info->idlers));

    /* If other threads are waiting on a worker, wake one up */
    if (prev_idlers < 0) {
        rv = apr_thread_mutex_lock(queue_info->idlers_mutex);
        if (rv != APR_SUCCESS) {
            AP_DEBUG_ASSERT(0);
            return rv;
        }
        rv = apr_thread_cond_signal(queue_info->wait_for_idler);
        if (rv != APR_SUCCESS) {
            apr_thread_mutex_unlock(queue_info->idlers_mutex);
            return rv;
        }
        rv = apr_thread_mutex_unlock(queue_info->idlers_mutex);
        if (rv != APR_SUCCESS) {
            return rv;
        }
    }

    return APR_SUCCESS;
}