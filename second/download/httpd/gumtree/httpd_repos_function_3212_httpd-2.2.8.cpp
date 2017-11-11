static apr_status_t thread_mutex_cleanup(void *themutex)
{
    apr_thread_mutex_t *mutex = themutex;
    return apr_thread_mutex_destroy(mutex);
}