static apr_status_t get_next(h2_slot *slot)
{
    h2_workers *workers = slot->workers;
    apr_status_t status;
    
    slot->task = NULL;
    while (!slot->aborted) {
        if (!slot->task) {
            status = h2_fifo_try_peek(workers->mplxs, mplx_peek, slot);
            if (status == APR_EOF) {
                return status;
            }
        }
        
        if (slot->task) {
            return APR_SUCCESS;
        }
        
        cleanup_zombies(workers);

        apr_thread_mutex_lock(slot->lock);
        push_slot(&workers->idle, slot);
        apr_thread_cond_wait(slot->not_idle, slot->lock);
        apr_thread_mutex_unlock(slot->lock);
    }
    return APR_EOF;
}