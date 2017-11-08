static apr_status_t threadproc_global_cleanup(void *ignored)
{
    DeleteCriticalSection(&proc_lock);
    return APR_SUCCESS;
}