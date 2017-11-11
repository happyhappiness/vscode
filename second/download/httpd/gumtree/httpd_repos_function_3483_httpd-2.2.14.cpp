static apr_status_t proc_mutex_proc_pthread_tryacquire(apr_proc_mutex_t *mutex)
{
    apr_status_t rv;
 
    if ((rv = pthread_mutex_trylock(mutex->pthread_interproc))) {
#ifdef HAVE_ZOS_PTHREADS 
        rv = errno;
#endif
        if (rv == EBUSY) {
            return APR_EBUSY;
        }
#ifdef HAVE_PTHREAD_MUTEX_ROBUST
        /* Okay, our owner died.  Let's try to make it consistent again. */
        if (rv == EOWNERDEAD) {
            pthread_mutex_consistent_np(mutex->pthread_interproc);
            rv = APR_SUCCESS;
        }
        else
            return rv;
#else
        return rv;
#endif
    }
    mutex->curr_locked = 1;
    return rv;
}