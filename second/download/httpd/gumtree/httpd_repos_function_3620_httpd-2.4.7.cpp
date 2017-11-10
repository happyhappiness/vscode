apr_status_t ap_queue_info_term(fd_queue_info_t *queue_info)
{
    apr_status_t rv;
    rv = apr_thread_mutex_lock(queue_info->idlers_mutex);
    if (rv != APR_SUCCESS) {
        return rv;
    }
    queue_info->terminated = 1;
    apr_thread_cond_broadcast(queue_info->wait_for_idler);
    return apr_thread_mutex_unlock(queue_info->idlers_mutex);
}