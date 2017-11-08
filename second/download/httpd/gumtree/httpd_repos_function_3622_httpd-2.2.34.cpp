static apr_status_t proc_mutex_proc_pthread_release(apr_proc_mutex_t *mutex)
{
    apr_status_t rv;

    mutex->curr_locked = 0;
    if ((rv = pthread_mutex_unlock(mutex->pthread_interproc))) {
#ifdef HAVE_ZOS_PTHREADS
        rv = errno;
#endif
        return rv;
    }
    return APR_SUCCESS;
}