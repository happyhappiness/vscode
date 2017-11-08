static apr_status_t proc_mutex_posix_release(apr_proc_mutex_t *mutex)
{
    mutex->curr_locked = 0;
    if (sem_post(mutex->psem_interproc) < 0) {
        /* any failure is probably fatal, so no big deal to leave
         * ->curr_locked at 0. */
        return errno;
    }
    return APR_SUCCESS;
}