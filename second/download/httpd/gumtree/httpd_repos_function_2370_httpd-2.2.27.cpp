static SOCKET remove_job(void)
{
    joblist *job;
    SOCKET sock;

    WaitForSingleObject(allowed_globals.jobsemaphore, INFINITE);
    apr_thread_mutex_lock(allowed_globals.jobmutex);

    if (shutdown_in_progress && !allowed_globals.jobhead) {
        apr_thread_mutex_unlock(allowed_globals.jobmutex);
        return (INVALID_SOCKET);
    }
    job = allowed_globals.jobhead;
    ap_assert(job);
    allowed_globals.jobhead = job->next;
    if (allowed_globals.jobhead == NULL)
        allowed_globals.jobtail = NULL;
    apr_thread_mutex_unlock(allowed_globals.jobmutex);
    sock = job->sock;
    free(job);

    return (sock);
}