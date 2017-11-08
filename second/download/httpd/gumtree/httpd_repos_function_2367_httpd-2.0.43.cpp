apr_status_t apr_queue_interrupt_all(apr_queue_t *queue)
{
    apr_status_t rv;
    Q_DBG( "intr all", queue);    
    if ((rv = apr_thread_mutex_lock(queue->one_big_mutex)) != APR_SUCCESS) {
        return rv;
    }
    apr_thread_cond_broadcast(queue->not_empty);
    apr_thread_cond_broadcast(queue->not_full);

    if ((rv = apr_thread_mutex_unlock(queue->one_big_mutex)) != APR_SUCCESS) {
        return rv;
    }

    return APR_SUCCESS;
}