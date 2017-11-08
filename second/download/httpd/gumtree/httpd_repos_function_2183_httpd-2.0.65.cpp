apr_status_t ap_queue_info_set_idle(fd_queue_info_t *queue_info,
                                    apr_pool_t *pool_to_recycle)
{
    apr_status_t rv;
    rv = apr_thread_mutex_lock(queue_info->idlers_mutex);
    if (rv != APR_SUCCESS) {
        return rv;
    }
    AP_DEBUG_ASSERT(queue_info->idlers >= 0);
    AP_DEBUG_ASSERT(queue_info->num_recycled < queue_info->max_idlers);
    if (pool_to_recycle) {
        queue_info->recycled_pools[queue_info->num_recycled++] =
            pool_to_recycle;
    }
    if (queue_info->idlers++ == 0) {
        /* Only signal if we had no idlers before. */
        apr_thread_cond_signal(queue_info->wait_for_idler);
    }
    rv = apr_thread_mutex_unlock(queue_info->idlers_mutex);
    if (rv != APR_SUCCESS) {
        return rv;
    }
    return APR_SUCCESS;
}