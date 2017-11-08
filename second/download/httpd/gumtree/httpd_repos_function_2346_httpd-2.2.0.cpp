apr_status_t ap_queue_info_set_idle(fd_queue_info_t *queue_info,
                                    apr_pool_t *pool_to_recycle)
{
    apr_status_t rv;
    int prev_idlers;

    /* If we have been given a pool to recycle, atomically link
     * it into the queue_info's list of recycled pools
     */
    if (pool_to_recycle) {
        struct recycled_pool *new_recycle;
        new_recycle = (struct recycled_pool *)apr_palloc(pool_to_recycle,
                                                         sizeof(*new_recycle));
        new_recycle->pool = pool_to_recycle;
        for (;;) {
            new_recycle->next = queue_info->recycled_pools;
            if (apr_atomic_casptr((volatile void**)&(queue_info->recycled_pools),
                                  new_recycle, new_recycle->next) ==
                new_recycle->next) {
                break;
            }
        }
    }

    /* Atomically increment the count of idle workers */
    for (;;) {
        prev_idlers = queue_info->idlers;
        if (apr_atomic_cas32(&(queue_info->idlers), prev_idlers + 1,
                             prev_idlers) == prev_idlers) {
            break;
        }
    }

    /* If this thread just made the idle worker count nonzero,
     * wake up the listener. */
    if (prev_idlers == 0) {
        rv = apr_thread_mutex_lock(queue_info->idlers_mutex);
        if (rv != APR_SUCCESS) {
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