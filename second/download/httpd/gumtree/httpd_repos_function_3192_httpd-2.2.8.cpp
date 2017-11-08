static apr_status_t proc_mutex_fcntl_acquire(apr_proc_mutex_t *mutex)
{
    int rc;

    do {
        rc = fcntl(mutex->interproc->filedes, F_SETLKW, &proc_mutex_lock_it);
    } while (rc < 0 && errno == EINTR);
    if (rc < 0) {
        return errno;
    }
    mutex->curr_locked=1;
    return APR_SUCCESS;
}