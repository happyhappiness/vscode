static void* APR_THREAD_FUNC slot_run(apr_thread_t *thread, void *wctx)
{
    h2_slot *slot = wctx;
    
    while (!slot->aborted) {

        /* Get a h2_task from the mplxs queue. */
        get_next(slot);
        while (slot->task) {
        
            h2_task_do(slot->task, thread, slot->id);
            
            /* Report the task as done. If stickyness is left, offer the
             * mplx the opportunity to give us back a new task right away.
             */
            if (!slot->aborted && (--slot->sticks > 0)) {
                h2_mplx_task_done(slot->task->mplx, slot->task, &slot->task);
            }
            else {
                h2_mplx_task_done(slot->task->mplx, slot->task, NULL);
                slot->task = NULL;
            }
        }
    }

    slot_done(slot);
    return NULL;
}