static apr_status_t proc_mutex_fcntl_destroy(apr_proc_mutex_t *mutex)
{
    apr_status_t rv;
    if ((rv = proc_mutex_fcntl_cleanup(mutex)) == APR_SUCCESS) {
        apr_pool_cleanup_kill(mutex->pool, mutex, proc_mutex_fcntl_cleanup);
        return APR_SUCCESS;
    }
    return rv;
}