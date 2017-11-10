static apr_status_t 
apr_thread_rwlock_wrlock_core(apr_thread_rwlock_t *rwlock, DWORD milliseconds)
{
    DWORD   code = WaitForSingleObject(rwlock->write_mutex, milliseconds);

    if (code == WAIT_FAILED || code == WAIT_TIMEOUT)
        return APR_FROM_OS_ERROR(code);

    /* We've got the writer lock but we have to wait for all readers to
     * unlock before it's ok to use it.
     */
    if (rwlock->readers) {
        /* Must wait for readers to finish before returning, unless this
         * is an trywrlock (milliseconds == 0):
         */
        code = milliseconds
          ? WaitForSingleObject(rwlock->read_event, milliseconds)
          : WAIT_TIMEOUT;
        
        if (code == WAIT_FAILED || code == WAIT_TIMEOUT) {
            /* Unable to wait for readers to finish, release write lock: */
            if (! ReleaseMutex(rwlock->write_mutex))
                return apr_get_os_error();
            
            return APR_FROM_OS_ERROR(code);
        }
    }

    return APR_SUCCESS;
}