static apr_status_t thread_cond_cleanup(void *data)
{
    struct waiter *w;
    apr_thread_cond_t *cond = (apr_thread_cond_t *)data;

    acquire_sem(cond->lock);
    delete_sem(cond->lock);

    return APR_SUCCESS;
}