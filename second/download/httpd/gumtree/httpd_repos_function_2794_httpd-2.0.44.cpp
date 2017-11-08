static apr_status_t thread_rwlock_cleanup(void *data)
{
    apr_thread_rwlock_t *rwlock = data;
    CloseHandle(rwlock->readevent);
    CloseHandle(rwlock->mutex);
    CloseHandle(rwlock->writemutex);
    return APR_SUCCESS;
}