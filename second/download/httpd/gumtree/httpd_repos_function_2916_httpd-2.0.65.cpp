static apr_status_t proc_mutex_cleanup(void *mutex_)
{
    apr_proc_mutex_t *mutex = mutex_;

    if (mutex->handle) {
        if (CloseHandle(mutex->handle) == 0) {
            return apr_get_os_error();
        }
    }
    return APR_SUCCESS;
}