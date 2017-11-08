static apr_status_t thread_rwlock_cleanup(void *data)
{
    apr_thread_rwlock_t *rwlock = (apr_thread_rwlock_t *)data;

    NXRwLockFree (rwlock->rwlock);
    return APR_SUCCESS;
}