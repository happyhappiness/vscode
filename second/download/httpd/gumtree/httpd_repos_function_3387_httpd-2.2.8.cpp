apr_status_t apr_thread_exit(apr_thread_t *thd,
                             apr_status_t retval)
{
    thd->exitval = retval;
    apr_pool_destroy(thd->pool);
    NXThreadExit(NULL);
    return APR_SUCCESS;
}