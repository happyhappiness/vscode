apr_status_t apr_queue_pop(apr_queue_t *queue, void **data)
{
    apr_status_t rv;
    int need_signal=0;

    if (queue->terminated) {
        return APR_EOF; /* no more elements ever again */
    }

    rv = apr_thread_mutex_lock(queue->one_big_mutex);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    /* Keep waiting until we wake up and find that the queue is not empty. */
    if (apr_queue_empty(queue)) {
        if (!queue->terminated) {
            rv = apr_thread_cond_wait(queue->not_empty, queue->one_big_mutex);
            if (rv != APR_SUCCESS) {
                apr_thread_mutex_unlock(queue->one_big_mutex);
                return rv;
            }
        }
        /* If we wake up and it's still empty, then we were interrupted */
        if (apr_queue_empty(queue)) {
            Q_DBG( "queue empty (intr)", queue);
            rv = apr_thread_mutex_unlock(queue->one_big_mutex);
            if (rv != APR_SUCCESS) {
                return rv;
            }
            if (queue->terminated) {
                return APR_EOF; /* no more elements ever again */
            }
            else {
                return APR_EINTR;
            }
        }
    } 
    if (apr_queue_full(queue)) {
        need_signal =1;
    }

    *data = &queue->data[queue->out];
    queue->nelts--;

    queue->out = (queue->out + 1) % queue->bounds;
    if ( need_signal == 1 ) {
        Q_DBG( "signal !full", queue);
        rv = apr_thread_cond_signal(queue->not_full);
        if ( rv != APR_SUCCESS) {
            apr_thread_mutex_unlock(queue->one_big_mutex);
            return rv;
        }
    }

    rv = apr_thread_mutex_unlock(queue->one_big_mutex);
    return rv;
}