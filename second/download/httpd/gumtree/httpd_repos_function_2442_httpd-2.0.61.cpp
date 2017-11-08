static apr_status_t queue_destroy(void *data) 
{
    apr_queue_t *queue = data;

    /* Ignore errors here, we can't do anything about them anyway. */

    apr_thread_cond_destroy(queue->not_empty);
    apr_thread_cond_destroy(queue->not_full);
    apr_thread_mutex_destroy(queue->one_big_mutex);

    return APR_SUCCESS;
}