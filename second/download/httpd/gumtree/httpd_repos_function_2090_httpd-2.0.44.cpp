apr_status_t ap_queue_info_wait_for_idler(fd_queue_info_t *queue_info,
                                          apr_pool_t **recycled_pool)
{
    apr_status_t rv;
    *recycled_pool = NULL;
    rv = apr_thread_mutex_lock(queue_info->idlers_mutex);
    if (rv != APR_SUCCESS) {
        return rv;
    }
    AP_DEBUG_ASSERT(queue_info->idlers >= 0);
    while ((queue_info->idlers == 0) && (!queue_info->terminated)) {
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
    queue_info->idlers--; /* Oh, and idler? Let's take 'em! */
    if (queue_info->num_recycled) {
        *recycled_pool =
            queue_info->recycled_pools[--queue_info->num_recycled];
    }
    rv = apr_thread_mutex_unlock(queue_info->idlers_mutex);
    if (rv != APR_SUCCESS) {
        return rv;
    }
    else if (queue_info->terminated) {
        return APR_EOF;
    }
    else {
        return APR_SUCCESS;
    }
}