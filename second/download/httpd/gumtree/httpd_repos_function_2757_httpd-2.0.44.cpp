static apr_status_t proc_mutex_posix_create(apr_proc_mutex_t *new_mutex,
                                            const char *fname)
{
    sem_t *psem;
    apr_status_t stat;
    char semname[14];
    apr_time_t now;
    unsigned long epoch;
    
    new_mutex->interproc = apr_palloc(new_mutex->pool,
                                      sizeof(*new_mutex->interproc));
    /*
     * This bogusness is to follow what appears to be the
     * lowest common denominator in Posix semaphore naming:
     *   - start with '/'
     *   - be at most 14 chars
     *   - be unique and not match anything on the filesystem
     *
     * Because of this, we ignore fname and craft our own.
     *
     * FIXME: There is a small window of opportunity where
     * instead of getting a new semaphore descriptor, we get
     * a previously obtained one. This can happen if the requests
     * are made at the "same time" (within a second, due to the
     * apr_time_now() call) and in the small span of time between
     * the sem_open and the sem_unlink. Use of O_EXCL does not
     * help here however...
     */
    now = apr_time_now();
    epoch = apr_time_sec(now);
    apr_snprintf(semname, sizeof(semname), "/ApR.%lx", epoch);
    psem = sem_open((const char *) semname, O_CREAT, 0644, 1);

    if (psem == (sem_t *)SEM_FAILED) {
        stat = errno;
        proc_mutex_posix_cleanup(new_mutex);
        return stat;
    }
    /* Ahhh. The joys of Posix sems. Predelete it... */
    sem_unlink((const char *) semname);
    new_mutex->interproc->filedes = (int)psem;	/* Ugg */
    apr_pool_cleanup_register(new_mutex->pool, (void *)new_mutex,
                              apr_proc_mutex_cleanup, 
                              apr_pool_cleanup_null);
    return APR_SUCCESS;
}