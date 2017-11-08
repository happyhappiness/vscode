static apr_status_t proc_mutex_proc_pthread_acquire(apr_proc_mutex_t *mutex)
{
    apr_status_t rv;

    if ((rv = pthread_mutex_lock(mutex->pthread_interproc))) {
#ifdef PTHREAD_SETS_ERRNO
        rv = errno;
#endif
#ifdef HAVE_PTHREAD_MUTEX_ROBUST
        /* Okay, our owner died.  Let's try to make it consistent again. */
        if (rv == EOWNERDEAD) {
            pthread_mutex_consistent_np(mutex->pthread_interproc);
        }
        else
            return rv;
#else
        return rv;
#endif
    }
    mutex->curr_locked = 1;
    return APR_SUCCESS;
}