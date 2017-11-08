static apr_status_t queue_interrupt(fd_queue_t * queue, int all)
{
    apr_status_t rv;

    if ((rv = apr_thread_mutex_lock(queue->one_big_mutex)) != APR_SUCCESS) {
        return rv;
    }
    if (all)
        apr_thread_cond_broadcast(queue->not_empty);
    else
        apr_thread_cond_signal(queue->not_empty);
    return apr_thread_mutex_unlock(queue->one_big_mutex);
}