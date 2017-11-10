static void free_proc_chain(struct process_chain *procs)
{
    /* Dispose of the subprocesses we've spawned off in the course of
     * whatever it was we're cleaning up now.  This may involve killing
     * some of them off...
     */
    struct process_chain *pc;
    int need_timeout = 0;
    apr_time_t timeout_interval;

    if (!procs)
        return; /* No work.  Whew! */

    /* First, check to see if we need to do the SIGTERM, sleep, SIGKILL
     * dance with any of the processes we're cleaning up.  If we've got
     * any kill-on-sight subprocesses, ditch them now as well, so they
     * don't waste any more cycles doing whatever it is that they shouldn't
     * be doing anymore.
     */

#ifndef NEED_WAITPID
    /* Pick up all defunct processes */
    for (pc = procs; pc; pc = pc->next) {
        if (apr_proc_wait(pc->proc, NULL, NULL, APR_NOWAIT) != APR_CHILD_NOTDONE)
            pc->kill_how = APR_KILL_NEVER;
    }
#endif /* !defined(NEED_WAITPID) */

    for (pc = procs; pc; pc = pc->next) {
#ifndef WIN32
        if ((pc->kill_how == APR_KILL_AFTER_TIMEOUT)
            || (pc->kill_how == APR_KILL_ONLY_ONCE)) {
            /*
             * Subprocess may be dead already.  Only need the timeout if not.
             * Note: apr_proc_kill on Windows is TerminateProcess(), which is
             * similar to a SIGKILL, so always give the process a timeout
             * under Windows before killing it.
             */
            if (apr_proc_kill(pc->proc, SIGTERM) == APR_SUCCESS)
                need_timeout = 1;
        }
        else if (pc->kill_how == APR_KILL_ALWAYS) {
#else /* WIN32 knows only one fast, clean method of killing processes today */
        if (pc->kill_how != APR_KILL_NEVER) {
            need_timeout = 1;
            pc->kill_how = APR_KILL_ALWAYS;
#endif
            apr_proc_kill(pc->proc, SIGKILL);
        }
    }

    /* Sleep only if we have to. The sleep algorithm grows
     * by a factor of two on each iteration. TIMEOUT_INTERVAL
     * is equal to TIMEOUT_USECS / 64.
     */
    if (need_timeout) {
        timeout_interval = TIMEOUT_INTERVAL;
        apr_sleep(timeout_interval);

        do {
            /* check the status of the subprocesses */
            need_timeout = 0;
            for (pc = procs; pc; pc = pc->next) {
                if (pc->kill_how == APR_KILL_AFTER_TIMEOUT) {
                    if (apr_proc_wait(pc->proc, NULL, NULL, APR_NOWAIT)
                            == APR_CHILD_NOTDONE)
                        need_timeout = 1;		/* subprocess is still active */
                    else
                        pc->kill_how = APR_KILL_NEVER;	/* subprocess has exited */
                }
            }
            if (need_timeout) {
                if (timeout_interval >= TIMEOUT_USECS) {
                    break;
                }
                apr_sleep(timeout_interval);
                timeout_interval *= 2;
            }
        } while (need_timeout);
    }

    /* OK, the scripts we just timed out for have had a chance to clean up
     * --- now, just get rid of them, and also clean up the system accounting
     * goop...
     */
    for (pc = procs; pc; pc = pc->next) {
        if (pc->kill_how == APR_KILL_AFTER_TIMEOUT)
            apr_proc_kill(pc->proc, SIGKILL);
    }

    /* Now wait for all the signaled processes to die */
    for (pc = procs; pc; pc = pc->next) {
        if (pc->kill_how != APR_KILL_NEVER)
            (void)apr_proc_wait(pc->proc, NULL, NULL, APR_WAIT);
    }
}


/*
 * Pool creation/destruction stubs, for people who are running
 * mixed release/debug enviroments.
 */

#if !APR_POOL_DEBUG
APR_DECLARE(void *) apr_palloc_debug(apr_pool_t *pool, apr_size_t size,
                                     const char *file_line)
{
    return apr_palloc(pool, size);
}

APR_DECLARE(void *) apr_pcalloc_debug(apr_pool_t *pool, apr_size_t size,
                                      const char *file_line)
{
    return apr_pcalloc(pool, size);
}

APR_DECLARE(void) apr_pool_clear_debug(apr_pool_t *pool,
                                       const char 