static apr_status_t slot_pull_task(h2_slot *slot, h2_mplx *m)
{
    apr_status_t rv;
    
    rv = h2_mplx_pop_task(m, &slot->task);
    if (slot->task) {
        /* Ok, we got something to give back to the worker for execution. 
         * If we still have idle workers, we let the worker be sticky, 
         * e.g. making it poll the task's h2_mplx instance for more work 
         * before asking back here. */
        slot->sticks = slot->workers->max_workers;
        return rv;            
    }
    slot->sticks = 0;
    return APR_EOF;
}