static apr_status_t proc_mutex_flock_release(apr_proc_mutex_t *mutex)
{
    int rc;

    mutex->curr_locked = 0;
    do {
        rc = flock(mutex->interproc->filedes, LOCK_UN);
    } while (rc < 0 && errno == EINTR);
    if (rc < 0) {
        return errno;
    }
    return APR_SUCCESS;
}