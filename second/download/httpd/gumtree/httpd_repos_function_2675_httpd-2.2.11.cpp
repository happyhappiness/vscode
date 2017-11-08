static apr_thread_pool_task_t *pop_task(apr_thread_pool_t * me)
{
    apr_thread_pool_task_t *task = NULL;
    int seg;

    /* check for scheduled tasks */
    if (me->scheduled_task_cnt > 0) {
        task = APR_RING_FIRST(me->scheduled_tasks);
        assert(task != NULL);
        assert(task !=
               APR_RING_SENTINEL(me->scheduled_tasks, apr_thread_pool_task,
                                 link));
        /* if it's time */
        if (task->dispatch.time <= apr_time_now()) {
            --me->scheduled_task_cnt;
            APR_RING_REMOVE(task, link);
            return task;
        }
    }
    /* check for normal tasks if we're not returning a scheduled task */
    if (me->task_cnt == 0) {
        return NULL;
    }

    task = APR_RING_FIRST(me->tasks);
    assert(task != NULL);
    assert(task != APR_RING_SENTINEL(me->tasks, apr_thread_pool_task, link));
    --me->task_cnt;
    seg = TASK_PRIORITY_SEG(task);
    if (task == me->task_idx[seg]) {
        me->task_idx[seg] = APR_RING_NEXT(task, link);
        if (me->task_idx[seg] == APR_RING_SENTINEL(me->tasks,
                                                   apr_thread_pool_task, link)
            || TASK_PRIORITY_SEG(me->task_idx[seg]) != seg) {
            me->task_idx[seg] = NULL;
        }
    }
    APR_RING_REMOVE(task, link);
    return task;
}