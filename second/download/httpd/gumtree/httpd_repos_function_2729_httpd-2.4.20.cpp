static h2_task *next_task(h2_workers *workers)
{
    h2_task *task = NULL;
    h2_mplx *last = NULL;
    int has_more;
    
    /* Get the next h2_mplx to process that has a task to hand out.
     * If it does, place it at the end of the queu and return the
     * task to the worker.
     * If it (currently) has no tasks, remove it so that it needs
     * to register again for scheduling.
     * If we run out of h2_mplx in the queue, we need to wait for
     * new mplx to arrive. Depending on how many workers do exist,
     * we do a timed wait or block indefinitely.
     */
    while (!task && !H2_MPLX_LIST_EMPTY(&workers->mplxs)) {
        h2_mplx *m = H2_MPLX_LIST_FIRST(&workers->mplxs);
        
        if (last == m) {
            break;
        }
        H2_MPLX_REMOVE(m);
        --workers->mplx_count;
        
        task = h2_mplx_pop_task(m, &has_more);
        if (has_more) {
            H2_MPLX_LIST_INSERT_TAIL(&workers->mplxs, m);
            ++workers->mplx_count;
            if (!last) {
                last = m;
            }
        }
    }
    return task;
}