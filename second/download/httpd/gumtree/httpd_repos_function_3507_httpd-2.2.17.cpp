static apr_status_t do_wait(apr_thread_cond_t *cond, apr_thread_mutex_t *mutex,
                            int timeout)
{
    struct waiter_t *wait;
    thread_id cth = find_thread(NULL);
    apr_status_t rv;
    int flags = B_RELATIVE_TIMEOUT;
    
    /* We must be the owner of the mutex or we can't do this... */    
    if (mutex->owner != cth) {
        /* What should we return??? */
        return APR_EINVAL;
    }

    acquire_sem(cond->lock);
    wait = APR_RING_FIRST(&cond->flist);
    if (wait)
        APR_RING_REMOVE(wait, link);
    else
        wait = make_waiter(cond->pool);   
    APR_RING_INSERT_TAIL(&cond->alist, wait, waiter_t, link);
    cond->condlock = mutex;
    release_sem(cond->lock);
       
    apr_thread_mutex_unlock(cond->condlock);

    if (timeout == 0)
        flags = 0;
        
    rv = acquire_sem_etc(wait->sem, 1, flags, timeout);

    apr_thread_mutex_lock(cond->condlock);
    
    if (rv != B_OK)
        if (rv == B_TIMED_OUT)
            return APR_TIMEUP;
        return rv;       

    acquire_sem(cond->lock);
    APR_RING_REMOVE(wait, link);
    APR_RING_INSERT_TAIL(&cond->flist, wait, waiter_t, link);
    release_sem(cond->lock);
    
    return APR_SUCCESS;
}