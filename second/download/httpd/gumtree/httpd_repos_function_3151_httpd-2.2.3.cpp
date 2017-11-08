static apr_status_t thread_rwlock_cleanup(void *therwlock)
{
    apr_thread_rwlock_t *rwlock = therwlock;
    return apr_thread_rwlock_destroy(rwlock);
}