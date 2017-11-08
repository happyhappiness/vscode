static apr_status_t proc_mutex_posix_acquire(apr_proc_mutex_t *mutex)
{
    if (sem_wait(mutex->psem_interproc) < 0) {
        return errno;
    }
    mutex->curr_locked = 1;
    return APR_SUCCESS;
}