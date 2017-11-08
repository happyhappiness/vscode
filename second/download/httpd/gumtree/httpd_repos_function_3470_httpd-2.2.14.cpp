static apr_status_t proc_mutex_posix_create(apr_proc_mutex_t *new_mutex,
                                            const char *fname)
{
    #define APR_POSIXSEM_NAME_MIN 13
    sem_t *psem;
    char semname[32];
    
    new_mutex->interproc = apr_palloc(new_mutex->pool,
                                      sizeof(*new_mutex->interproc));
    /*
     * This bogusness is to follow what appears to be the
     * lowest common denominator in Posix semaphore naming:
     *   - start with '/'
     *   - be at most 14 chars
     *   - be unique and not match anything on the filesystem
     *
     * Because of this, we use fname to generate a (unique) hash
     * and use that as the name of the semaphore. If no filename was
     * given, we create one based on the time. We tuck the name
     * away, since it might be useful for debugging. We use 2 hashing
     * functions to try to avoid collisions.
     *
     * To  make this as robust as possible, we initially try something
     * larger (and hopefully more unique) and gracefully fail down to the
     * LCD above.
     *
     * NOTE: Darwin (Mac OS X) seems to be the most restrictive
     * implementation. Versions previous to Darwin 6.2 had the 14
     * char limit, but later rev's allow up to 31 characters.
     *
     */
    if (fname) {
        apr_ssize_t flen = strlen(fname);
        char *p = apr_pstrndup(new_mutex->pool, fname, strlen(fname));
        unsigned int h1, h2;
        h1 = apr_hashfunc_default((const char *)p, &flen);
        h2 = rshash(p);
        apr_snprintf(semname, sizeof(semname), "/ApR.%xH%x", h1, h2);
    } else {
        apr_time_t now;
        unsigned long sec;
        unsigned long usec;
        now = apr_time_now();
        sec = apr_time_sec(now);
        usec = apr_time_usec(now);
        apr_snprintf(semname, sizeof(semname), "/ApR.%lxZ%lx", sec, usec);
    }
    psem = sem_open(semname, O_CREAT | O_EXCL, 0644, 1);
    if (psem == (sem_t *)SEM_FAILED) {
        if (errno == ENAMETOOLONG) {
            /* Oh well, good try */
            semname[APR_POSIXSEM_NAME_MIN] = '\0';
        } else {
            return errno;
        }
        psem = sem_open(semname, O_CREAT | O_EXCL, 0644, 1);
    }

    if (psem == (sem_t *)SEM_FAILED) {
        return errno;
    }
    /* Ahhh. The joys of Posix sems. Predelete it... */
    sem_unlink(semname);
    new_mutex->psem_interproc = psem;
    new_mutex->fname = apr_pstrdup(new_mutex->pool, semname);
    apr_pool_cleanup_register(new_mutex->pool, (void *)new_mutex,
                              apr_proc_mutex_cleanup, 
                              apr_pool_cleanup_null);
    return APR_SUCCESS;
}