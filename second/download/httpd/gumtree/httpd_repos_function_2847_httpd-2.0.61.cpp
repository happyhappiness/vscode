static apr_status_t proc_mutex_posix_create(apr_proc_mutex_t *new_mutex,
                                            const char *fname)
{
    sem_t *psem;
    apr_status_t stat;
    char semname[31];
    apr_time_t now;
    unsigned long sec;
    unsigned long usec;
    
    new_mutex->interproc = apr_palloc(new_mutex->pool,
                                      sizeof(*new_mutex->interproc));
    new_mutex->interproc->filedes = -1;
    /*
     * This bogusness is to follow what appears to be the
     * lowest common denominator in Posix semaphore naming:
     *   - start with '/'
     *   - be at most 14 chars
     *   - be unique and not match anything on the filesystem
     *
     * Because of this, we ignore fname, and try our
     * own naming system. We tuck the name away, since it might
     * be useful for debugging. to  make this as robust as possible,
     * we initially try something larger (and hopefully more unique)
     * and gracefully fail down to the LCD above.
     *
     * NOTE: Darwin (Mac OS X) seems to be the most restrictive
     * implementation. Versions previous to Darwin 6.2 had the 14
     * char limit, but later rev's allow up to 31 characters.
     *
     * FIXME: There is a small window of opportunity where
     * instead of getting a new semaphore descriptor, we get
     * a previously obtained one. This can happen if the requests
     * are made at the "same time" and in the small span of time between
     * the sem_open and the sem_unlink. Use of O_EXCL does not
     * help here however...
     *
     */
    now = apr_time_now();
    sec = apr_time_sec(now);
    usec = apr_time_usec(now);
    apr_snprintf(semname, sizeof(semname), "/ApR.%lxZ%lx", sec, usec);
    psem = sem_open((const char *) semname, O_CREAT, 0644, 1);
    if ((psem == (sem_t *)SEM_FAILED) && (errno == ENAMETOOLONG)) {
        /* Oh well, good try */
        semname[13] = '\0';
        psem = sem_open((const char *) semname, O_CREAT, 0644, 1);
    }

    if (psem == (sem_t *)SEM_FAILED) {
        stat = errno;
        proc_mutex_posix_cleanup(new_mutex);
        return stat;
    }
    /* Ahhh. The joys of Posix sems. Predelete it... */
    sem_unlink((const char *) semname);
    new_mutex->interproc->filedes = (int)psem;	/* Ugg */
    new_mutex->fname = apr_pstrdup(new_mutex->pool, semname);
    apr_pool_cleanup_register(new_mutex->pool, (void *)new_mutex,
                              apr_proc_mutex_cleanup, 
                              apr_pool_cleanup_null);
    return APR_SUCCESS;
}