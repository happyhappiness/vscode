static apr_status_t proc_mutex_fcntl_cleanup(void *mutex_)
{
    apr_status_t status;
    apr_proc_mutex_t *mutex=mutex_;

    if (mutex->curr_locked == 1) {
        status = proc_mutex_fcntl_release(mutex);
        if (status != APR_SUCCESS)
            return status;
    }
    if (mutex->interproc) { /* if it was opened successfully */
        apr_file_close(mutex->interproc);
    }
    return APR_SUCCESS;
}