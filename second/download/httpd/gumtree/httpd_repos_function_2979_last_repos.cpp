static apr_status_t workers_pool_cleanup(void *data)
{
    h2_workers *workers = data;
    h2_slot *slot;
    
    if (!workers->aborted) {
        workers->aborted = 1;
        /* abort all idle slots */
        for (;;) {
            slot = pop_slot(&workers->idle);
            if (slot) {
                apr_thread_mutex_lock(slot->lock);
                slot->aborted = 1;
                apr_thread_cond_signal(slot->not_idle);
                apr_thread_mutex_unlock(slot->lock);
            }
            else {
                break;
            }
        }

        h2_fifo_term(workers->mplxs);
        h2_fifo_interrupt(workers->mplxs);

        cleanup_zombies(workers);
    }
    return APR_SUCCESS;
}