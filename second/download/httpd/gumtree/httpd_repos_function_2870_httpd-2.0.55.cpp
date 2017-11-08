static apr_status_t thread_mutex_cleanup(void *data)
{
    apr_thread_mutex_t *lock = data;

    if (lock->type == thread_mutex_critical_section) {
        DeleteCriticalSection(&lock->section);
    }
    else {
        if (!CloseHandle(lock->handle)) {
            return apr_get_os_error();
        }
    }
    return APR_SUCCESS;
}