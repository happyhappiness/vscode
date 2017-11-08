static apr_status_t thread_rwlock_cleanup(void *data)
{
    return apr_thread_rwlock_destroy((apr_thread_rwlock_t *) data);
}