static apr_status_t apr_thread_rwlock_rdlock_core(apr_thread_rwlock_t *rwlock,
                                                  DWORD  milliseconds)
{
    DWORD   code = WaitForSingleObject(rwlock->write_mutex, milliseconds);

    if (code == WAIT_FAILED || code == WAIT_TIMEOUT)
        return APR_FROM_OS_ERROR(code);

    /* We've successfully acquired the writer mutex, we can't be locked
     * for write, so it's OK to add the reader lock.  The writer mutex
     * doubles as race condition protection for the readers counter.   
     */
    InterlockedIncrement(&rwlock->readers);
    
    if (! ResetEvent(rwlock->read_event))
        return apr_get_os_error();
    
    if (! ReleaseMutex(rwlock->write_mutex))
        return apr_get_os_error();
    
    return APR_SUCCESS;
}