static apr_status_t thread_rwlock_cleanup(void *data)
{
    apr_thread_rwlock_t *rwlock = (apr_thread_rwlock_t *)data;
    apr_status_t stat;

    stat = pthread_rwlock_destroy(&rwlock->rwlock);
#ifdef HAVE_ZOS_PTHREADS
    if (stat) {
        stat = errno;
    }
#endif
    return stat;
}