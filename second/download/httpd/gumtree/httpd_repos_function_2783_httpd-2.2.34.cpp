static apr_status_t remove_scheduled_tasks(apr_thread_pool_t *me,
                                           void *owner)
{
    apr_thread_pool_task_t *t_loc;
    apr_thread_pool_task_t *next;

    t_loc = APR_RING_FIRST(me->scheduled_tasks);
    while (t_loc !=
           APR_RING_SENTINEL(me->scheduled_tasks, apr_thread_pool_task,
                             link)) {
        next = APR_RING_NEXT(t_loc, link);
        /* if this is the owner remove it */
        if (t_loc->owner == owner) {
            --me->scheduled_task_cnt;
            APR_RING_REMOVE(t_loc, link);
        }
        t_loc = next;
    }
    return APR_SUCCESS;
}