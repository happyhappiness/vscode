static apr_status_t ififo_destroy(void *data) 
{
    h2_ififo *fifo = data;

    apr_thread_cond_destroy(fifo->not_empty);
    apr_thread_cond_destroy(fifo->not_full);
    apr_thread_mutex_destroy(fifo->lock);

    return APR_SUCCESS;
}