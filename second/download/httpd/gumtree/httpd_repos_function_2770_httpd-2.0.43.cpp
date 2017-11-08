static apr_status_t proc_mutex_proc_pthread_release(apr_proc_mutex_t *mutex)
{
    apr_status_t rv;

    if ((rv = pthread_mutex_unlock(mutex->pthread_interproc))) {
#ifdef PTHREAD_SETS_ERRNO
        rv = errno;
#endif
        return rv;
    }
    mutex->curr_locked = 0;
    return APR_SUCCESS;
}