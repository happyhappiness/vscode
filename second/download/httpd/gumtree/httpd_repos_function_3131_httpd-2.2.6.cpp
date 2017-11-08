static apr_status_t proc_mutex_posix_cleanup(void *mutex_)
{
    apr_proc_mutex_t *mutex = mutex_;
    
    if (sem_close(mutex->psem_interproc) < 0) {
        return errno;
    }

    return APR_SUCCESS;
}