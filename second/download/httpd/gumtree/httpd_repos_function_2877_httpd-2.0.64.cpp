static apr_status_t proc_mutex_posix_release(apr_proc_mutex_t *mutex)
{
    int rc;

    mutex->curr_locked = 0;
    if ((rc = sem_post((sem_t *)mutex->interproc->filedes)) < 0) {
        return errno;
    }
    return APR_SUCCESS;
}