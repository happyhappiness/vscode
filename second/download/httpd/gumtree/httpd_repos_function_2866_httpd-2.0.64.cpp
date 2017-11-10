static apr_status_t thread_mutex_cleanup(void *data)
{
    apr_thread_mutex_t *mutex = (apr_thread_mutex_t *)data;

    NXMutexFree(mutex->mutex);        
    return APR_SUCCESS;
}