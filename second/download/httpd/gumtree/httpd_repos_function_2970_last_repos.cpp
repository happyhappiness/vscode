static apr_status_t activate_slot(h2_workers *workers, h2_slot *slot) 
{
    apr_status_t status;
    
    slot->workers = workers;
    slot->aborted = 0;
    slot->task = NULL;

    if (!slot->lock) {
        status = apr_thread_mutex_create(&slot->lock,
                                         APR_THREAD_MUTEX_DEFAULT,
                                         workers->pool);
        if (status != APR_SUCCESS) {
            push_slot(&workers->free, slot);
            return status;
        }
    }

    if (!slot->not_idle) {
        status = apr_thread_cond_create(&slot->not_idle, workers->pool);
        if (status != APR_SUCCESS) {
            push_slot(&workers->free, slot);
            return status;
        }
    }
    
    /* thread will either immediately start work or add itself
     * to the idle queue */
    apr_thread_create(&slot->thread, workers->thread_attr, slot_run, slot, 
                      workers->pool);
    if (!slot->thread) {
        push_slot(&workers->free, slot);
        return APR_ENOMEM;
    }
    
    apr_atomic_inc32(&workers->worker_count);
    return APR_SUCCESS;
}