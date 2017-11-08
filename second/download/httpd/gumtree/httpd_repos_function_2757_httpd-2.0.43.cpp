static apr_status_t proc_mutex_posix_destroy(apr_proc_mutex_t *mutex)
{
    apr_status_t stat;

    if ((stat = proc_mutex_posix_cleanup(mutex)) == APR_SUCCESS) {
        apr_pool_cleanup_kill(mutex->pool, mutex, proc_mutex_posix_cleanup);
        return APR_SUCCESS;
    }
    return stat;
}