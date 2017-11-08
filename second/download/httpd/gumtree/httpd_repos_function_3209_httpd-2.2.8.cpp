static apr_status_t thread_rwlock_cleanup(void *data)
{
    apr_thread_rwlock_t *rwlock = data;
    
    if (! CloseHandle(rwlock->read_event))
        return apr_get_os_error();

    if (! CloseHandle(rwlock->write_mutex))
        return apr_get_os_error();
    
    return APR_SUCCESS;
}