static APR_INLINE apr_status_t _thread_cond_timedwait(apr_thread_cond_t *cond,
                                                      apr_thread_mutex_t *mutex,
                                                      DWORD timeout_ms )
{
    DWORD res;

    while (1) {
        cond->num_waiting++;

        apr_thread_mutex_unlock(mutex);
        res = WaitForSingleObject(cond->event, timeout_ms);
        apr_thread_mutex_lock(mutex);
        cond->num_waiting--;
        if (res != WAIT_OBJECT_0) {
            apr_status_t rv = apr_get_os_error();
            if (res == WAIT_TIMEOUT) {
                return APR_TIMEUP;
            }
            return apr_get_os_error();
        }
        if (cond->signal_all) {
            if (cond->num_waiting == 0) {
                cond->signal_all = 0;
                cond->signalled = 0;
                ResetEvent(cond->event);
            }
            break;
        }
        else if (cond->signalled) {
            cond->signalled = 0;
            ResetEvent(cond->event);
            break;
        }
    }
    return APR_SUCCESS;
}