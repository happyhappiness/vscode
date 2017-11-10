static APR_INLINE apr_status_t _thread_cond_timedwait(apr_thread_cond_t *cond,
                                                      apr_thread_mutex_t *mutex,
                                                      DWORD timeout_ms )
{
    DWORD res;
    apr_status_t rv;
    unsigned int wake = 0;
    unsigned long generation;

    EnterCriticalSection(&cond->csection);
    cond->num_waiting++;
    generation = cond->generation;
    LeaveCriticalSection(&cond->csection);

    apr_thread_mutex_unlock(mutex);

    do {
        res = WaitForSingleObject(cond->semaphore, timeout_ms);

        EnterCriticalSection(&cond->csection);

        if (cond->num_wake) {
            if (cond->generation != generation) {
                cond->num_wake--;
                cond->num_waiting--;
                rv = APR_SUCCESS;
                break;
            } else {
                wake = 1;
            }
        }
        else if (res != WAIT_OBJECT_0) {
            cond->num_waiting--;
            rv = APR_TIMEUP;
            break;
        }

        LeaveCriticalSection(&cond->csection);

        if (wake) {
            wake = 0;
            ReleaseSemaphore(cond->semaphore, 1, NULL);
        }
    } while (1);

    LeaveCriticalSection(&cond->csection);
    apr_thread_mutex_lock(mutex);

    return rv;
}