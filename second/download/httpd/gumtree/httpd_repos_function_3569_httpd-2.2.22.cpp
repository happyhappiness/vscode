static apr_status_t proc_mutex_sysv_release(apr_proc_mutex_t *mutex)
{
    int rc;

    mutex->curr_locked = 0;
    do {
        rc = semop(mutex->interproc->filedes, &proc_mutex_op_off, 1);
    } while (rc < 0 && errno == EINTR);
    if (rc < 0) {
        return errno;
    }
    return APR_SUCCESS;
}