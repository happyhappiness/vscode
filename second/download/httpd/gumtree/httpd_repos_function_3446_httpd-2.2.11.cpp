static apr_status_t proc_mutex_sysv_tryacquire(apr_proc_mutex_t *mutex)
{
    int rc;

    do {
        rc = semop(mutex->interproc->filedes, &proc_mutex_op_try, 1);
    } while (rc < 0 && errno == EINTR);
    if (rc < 0) {
        if (errno == EAGAIN) {
            return APR_EBUSY;
        }
        return errno;
    }
    mutex->curr_locked = 1;
    return APR_SUCCESS;
}