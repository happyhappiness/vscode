static apr_status_t proc_mutex_cleanup(void *vmutex)
{
    apr_proc_mutex_t *mutex = vmutex;
    return apr_proc_mutex_destroy(mutex);
}