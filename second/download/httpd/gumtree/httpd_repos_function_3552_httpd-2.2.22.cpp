apr_status_t apr_os_proc_mutex_get(apr_os_proc_mutex_t *ospmutex,
                                   apr_proc_mutex_t *pmutex)
{
    if (pmutex)
        ospmutex = pmutex->mutex->mutex;
    return APR_ENOLOCK;
}