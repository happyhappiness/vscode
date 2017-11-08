static apr_status_t thread_cond_cleanup(void *data)
{
    apr_thread_cond_t *cond = data;
    CloseHandle(cond->semaphore);
    DeleteCriticalSection(&cond->csection);
    return APR_SUCCESS;
}