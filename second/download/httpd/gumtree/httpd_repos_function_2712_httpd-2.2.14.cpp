static apr_status_t remove_tasks(apr_thread_pool_t *me, void *owner)
{
    apr_thread_pool_task_t *t_loc;
    apr_thread_pool_task_t *next;
    int seg;

    t_loc = APR_RING_FIRST(me->tasks);
    while (t_loc != APR_RING_SENTINEL(me->tasks, apr_thread_pool_task, link)) {
        next = APR_RING_NEXT(t_loc, link);
        if (t_loc->owner == owner) {
            --me->task_cnt;
            seg = TASK_PRIORITY_SEG(t_loc);
            if (t_loc == me->task_idx[seg]) {
                me->task_idx[seg] = APR_RING_NEXT(t_loc, link);
                if (me->task_idx[seg] == APR_RING_SENTINEL(me->tasks,
                                                           apr_thread_pool_task,
                                                           link)
                    || TASK_PRIORITY_SEG(me->task_idx[seg]) != seg) {
                    me->task_idx[seg] = NULL;
                }
            }
            APR_RING_REMOVE(t_loc, link);
        }
        t_loc = next;
    }
    return APR_SUCCESS;
}