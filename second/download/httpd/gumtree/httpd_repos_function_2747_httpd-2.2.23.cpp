static apr_status_t add_task(apr_thread_pool_t *me, apr_thread_start_t func,
                             void *param, apr_byte_t priority, int push,
                             void *owner)
{
    apr_thread_pool_task_t *t;
    apr_thread_pool_task_t *t_loc;
    apr_thread_t *thd;
    apr_status_t rv = APR_SUCCESS;

    apr_thread_mutex_lock(me->lock);

    t = task_new(me, func, param, priority, owner, 0);
    if (NULL == t) {
        apr_thread_mutex_unlock(me->lock);
        return APR_ENOMEM;
    }

    t_loc = add_if_empty(me, t);
    if (NULL == t_loc) {
        goto FINAL_EXIT;
    }

    if (push) {
        while (APR_RING_SENTINEL(me->tasks, apr_thread_pool_task, link) !=
               t_loc && t_loc->dispatch.priority >= t->dispatch.priority) {
            t_loc = APR_RING_NEXT(t_loc, link);
        }
    }
    APR_RING_INSERT_BEFORE(t_loc, t, link);
    if (!push) {
        if (t_loc == me->task_idx[TASK_PRIORITY_SEG(t)]) {
            me->task_idx[TASK_PRIORITY_SEG(t)] = t;
        }
    }

  FINAL_EXIT:
    me->task_cnt++;
    if (me->task_cnt > me->tasks_high)
        me->tasks_high = me->task_cnt;
    if (0 == me->thd_cnt || (0 == me->idle_cnt && me->thd_cnt < me->thd_max &&
                             me->task_cnt > me->threshold)) {
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