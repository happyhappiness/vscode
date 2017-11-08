static apr_status_t proc_mutex_sysv_cleanup(void *mutex_)
{
    apr_proc_mutex_t *mutex=mutex_;
    union semun ick;
    
    if (mutex->interproc->filedes != -1) {
        ick.val = 0;
        semctl(mutex->interproc->filedes, 0, IPC_RMID, ick);
    }
    return APR_SUCCESS;
}