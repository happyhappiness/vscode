apr_status_t apr_threadproc_init(apr_pool_t *pool)
{
    IF_WIN_OS_IS_UNICODE
    {
        InitializeCriticalSection(&proc_lock);
        /* register the cleanup */
        apr_pool_cleanup_register(pool, &proc_lock,
                                  threadproc_global_cleanup,
                                  apr_pool_cleanup_null);
    }
    return APR_SUCCESS;
}