apr_status_t apr_queue_trypush(apr_queue_t *queue, void *data)
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

    if (apr_queue_full(queue)) {
        rv = apr_thread_mutex_unlock(queue->one_big_mutex);
        return APR_EAGAIN;
    }

    /* if we were empty then signal that we aren't */
    if (apr_queue_empty(queue)) {
        need_signal=1;
    }
    
    queue->data[queue->in] = data;
    queue->in = (queue->in +1) % queue->bounds ;
    queue->nelts++;

    if ( need_signal == 1 ) {
        Q_DBG( "sig !empty", queue);
        rv  = apr_thread_cond_signal(queue->not_empty);
        if ( rv != APR_SUCCESS) {
            apr_thread_mutex_unlock(queue->one_big_mutex);
            return rv;
        }
    }

    rv = apr_thread_mutex_unlock(queue->one_big_mutex);
    return rv;
}