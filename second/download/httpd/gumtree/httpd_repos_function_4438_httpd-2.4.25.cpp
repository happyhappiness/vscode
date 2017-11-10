apr_status_t ap_queue_pop(fd_queue_t *queue, apr_socket_t **sd, apr_pool_t **p)
{
    fd_queue_elem_t *elem;
    apr_status_t rv;

    if ((rv = apr_thread_mutex_lock(queue->one_big_mutex)) != APR_SUCCESS) {
        return rv;
    }

    /* Keep waiting until we wake up and find that the queue is not empty. */
    if (ap_queue_empty(queue)) {
        if (!queue->terminated) {
            apr_thread_cond_wait(queue->not_empty, queue->one_big_mutex);
        }
        /* If we wake up and it's still empty, then we were interrupted */
        if (ap_queue_empty(queue)) {
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

    elem = &queue->data[queue->out];
    queue->out++;
    if (queue->out >= queue->bounds)
        queue->out -= queue->bounds;
    queue->nelts--;
    *sd = elem->sd;
    *p = elem->p;
#ifdef AP_DEBUG
    elem->sd = NULL;
    elem->p = NULL;
#endif /* AP_DEBUG */

    rv = apr_thread_mutex_unlock(queue->one_big_mutex);
    return rv;
}