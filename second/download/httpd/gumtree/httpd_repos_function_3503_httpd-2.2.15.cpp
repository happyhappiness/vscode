static apr_status_t proc_mutex_proc_pthread_cleanup(void *mutex_)
{
    apr_proc_mutex_t *mutex=mutex_;
    apr_status_t rv;

    if (mutex->curr_locked == 1) {
        if ((rv = pthread_mutex_unlock(mutex->pthread_interproc))) {
#ifdef HAVE_ZOS_PTHREADS
            rv = errno;
#endif
            return rv;
        }
    }
    /* curr_locked is set to -1 until the mutex has been created */
    if (mutex->curr_locked != -1) {
        if ((rv = pthread_mutex_destroy(mutex->pthread_interproc))) {
#ifdef HAVE_ZOS_PTHREADS
            rv = errno;
#endif
            return rv;
        }
    }
    if (munmap((caddr_t)mutex->pthread_interproc, sizeof(pthread_mutex_t))) {
        return errno;
    }
    return APR_SUCCESS;
}