static apr_status_t proc_mutex_posix_cleanup(void *mutex_)
{
    apr_proc_mutex_t *mutex=mutex_;
    apr_status_t stat = APR_SUCCESS;
    
    if (mutex->interproc->filedes != -1) {
        if (sem_close((sem_t *)mutex->interproc->filedes) < 0) {
            stat = errno;
        }
    }
    return stat;
}