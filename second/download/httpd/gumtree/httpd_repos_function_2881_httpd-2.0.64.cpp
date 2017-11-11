static apr_status_t proc_mutex_sysv_create(apr_proc_mutex_t *new_mutex,
                                           const char *fname)
{
    union semun ick;
    apr_status_t rv;
    
    new_mutex->interproc = apr_palloc(new_mutex->pool, sizeof(*new_mutex->interproc));
    new_mutex->interproc->filedes = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600);

    if (new_mutex->interproc->filedes < 0) {
        rv = errno;
        proc_mutex_sysv_cleanup(new_mutex);
        return rv;
    }
    ick.val = 1;
    if (semctl(new_mutex->interproc->filedes, 0, SETVAL, ick) < 0) {
        rv = errno;
        proc_mutex_sysv_cleanup(new_mutex);
        return rv;
    }
    new_mutex->curr_locked = 0;
    apr_pool_cleanup_register(new_mutex->pool,
                              (void *)new_mutex, apr_proc_mutex_cleanup, 
                              apr_pool_cleanup_null);
    return APR_SUCCESS;
}