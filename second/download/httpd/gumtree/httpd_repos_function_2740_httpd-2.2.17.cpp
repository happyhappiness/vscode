static apr_status_t schedule_task(apr_thread_pool_t *me,
                                  apr_thread_start_t func, void *param,
                                  void *owner, apr_interval_time_t time)
{
    apr_thread_pool_task_t *t;
    apr_thread_pool_task_t *t_loc;
    apr_thread_t *thd;
    apr_status_t rv = APR_SUCCESS;
    apr_thread_mutex_lock(me->lock);

    t = task_new(me, func, param, 0, owner, time);
    if (NULL == t) {
        apr_thread_mutex_unlock(me->lock);
        return APR_ENOMEM;
    }
    t_loc = APR_RING_FIRST(me->scheduled_tasks);
    while (NULL != t_loc) {
        /* if the time is less than the entry insert ahead of it */
        if (t->dispatch.time < t_loc->dispatch.time) {
            ++me->scheduled_task_cnt;
            APR_RING_INSERT_BEFORE(t_loc, t, link);
            break;
        }
        else {
            t_loc = APR_RING_NEXT(t_loc, link);
            if (t_loc ==
                APR_RING_SENTINEL(me->scheduled_tasks, apr_thread_pool_task,
                                  link)) {
                ++me->scheduled_task_cnt;
                APR_RING_INSERT_TAIL(me->scheduled_tasks, t,
                                     apr_thread_pool_task, link);
                break;
            }
        }
    }
    /* there should be at least one thread for scheduled tasks */
    if (0 == me->thd_cnt) {
        rv = apr_thread_create(&thd, NULL, thread_pool_func, me, me->pool);
        if (APR_SUCCESS == rv) {
            ++me->thd_cnt;
            if (me->thd_cnt > me->thd_high)
                me->thd_high = me->thd_cnt;
        }
    }
    apr_thread_cond_signal(me->cond);
    apr_thread_mutex_unlock(me->lock);
    return rv;
}