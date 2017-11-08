static apr_status_t proc_mutex_posix_tryacquire(apr_proc_mutex_t *mutex)
{
    if (sem_trywait(mutex->psem_interproc) < 0) {
        if (errno == EAGAIN) {
            return APR_EBUSY;
        }
        return errno;
    }
    mutex->curr_locked = 1;
    return APR_SUCCESS;
}