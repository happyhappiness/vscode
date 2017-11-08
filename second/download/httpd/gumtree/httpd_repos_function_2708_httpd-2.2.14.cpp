static apr_thread_pool_task_t *add_if_empty(apr_thread_pool_t * me,
                                            apr_thread_pool_task_t * const t)
{
    int seg;
    int next;
    apr_thread_pool_task_t *t_next;

    seg = TASK_PRIORITY_SEG(t);
    if (me->task_idx[seg]) {
        assert(APR_RING_SENTINEL(me->tasks, apr_thread_pool_task, link) !=
               me->task_idx[seg]);
        t_next = me->task_idx[seg];
        while (t_next->dispatch.priority > t->dispatch.priority) {
            t_next = APR_RING_NEXT(t_next, link);
            if (APR_RING_SENTINEL(me->tasks, apr_thread_pool_task, link) ==
                t_next) {
                return t_next;
            }
        }
        return t_next;
    }

    for (next = seg - 1; next >= 0; next--) {
        if (me->task_idx[next]) {
            APR_RING_INSERT_BEFORE(me->task_idx[next], t, link);
            break;
        }
    }
    if (0 > next) {
        APR_RING_INSERT_TAIL(me->tasks, t, apr_thread_pool_task, link);
    }
    me->task_idx[seg] = t;
    return NULL;
}