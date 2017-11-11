static void *APR_THREAD_FUNC thread_pool_func(apr_thread_t * t, void *param)
{
    apr_status_t rv = APR_SUCCESS;
    apr_thread_pool_t *me = param;
    apr_thread_pool_task_t *task = NULL;
    apr_interval_time_t wait;
    struct apr_thread_list_elt *elt;

    apr_thread_mutex_lock(me->lock);
    elt = elt_new(me, t);
    if (!elt) {
        apr_thread_mutex_unlock(me->lock);
        apr_thread_exit(t, APR_ENOMEM);
    }

    while (!me->terminated && elt->state != TH_STOP) {
        /* Test if not new element, it is awakened from idle */
        if (APR_RING_NEXT(elt, link) != elt) {
            --me->idle_cnt;
            APR_RING_REMOVE(elt, link);
        }

        APR_RING_INSERT_TAIL(me->busy_thds, elt, apr_thread_list_elt, link);
        task = pop_task(me);
        while (NULL != task && !me->terminated) {
            ++me->tasks_run;
            elt->current_owner = task->owner;
            apr_thread_mutex_unlock(me->lock);
            apr_thread_data_set(task, "apr_thread_pool_task", NULL, t);
            task->func(t, task->param);
            apr_thread_mutex_lock(me->lock);
            APR_RING_INSERT_TAIL(me->recycled_tasks, task,
                                 apr_thread_pool_task, link);
            elt->current_owner = NULL;
            if (TH_STOP == elt->state) {
                break;
            }
            task = pop_task(me);
        }
        assert(NULL == elt->current_owner);
        if (TH_STOP != elt->state)
            APR_RING_REMOVE(elt, link);

        /* Test if a busy thread been asked to stop, which is not joinable */
        if ((me->idle_cnt >= me->idle_max
             && !(me->scheduled_task_cnt && 0 >= me->idle_max)
             && !me->idle_wait)
            || me->terminated || elt->state != TH_RUN) {
            --me->thd_cnt;
            if ((TH_PROBATION == elt->state) && me->idle_wait)
                ++me->thd_timed_out;
            APR_RING_INSERT_TAIL(me->recycled_thds, elt,
                                 apr_thread_list_elt, link);
            apr_thread_mutex_unlock(me->lock);
            apr_thread_detach(t);
            apr_thread_exit(t, APR_SUCCESS);
            return NULL;        /* should not be here, safe net */
        }

        /* busy thread become idle */
        ++me->idle_cnt;
        APR_RING_INSERT_TAIL(me->idle_thds, elt, apr_thread_list_elt, link);

        /* 
         * If there is a scheduled task, always scheduled to perform that task.
         * Since there is no guarantee that current idle threads are scheduled
         * for next scheduled task.
         */
        if (me->scheduled_task_cnt)
            wait = waiting_time(me);
        else if (me->idle_cnt > me->idle_max) {
            wait = me->idle_wait;
            elt->state = TH_PROBATION;
        }
        else
            wait = -1;

        if (wait >= 0) {
            rv = apr_thread_cond_timedwait(me->cond, me->lock, wait);
        }
        else {
            rv = apr_thread_cond_wait(me->cond, me->lock);
        }
    }

    /* idle thread been asked to stop, will be joined */
    --me->thd_cnt;
    apr_thread_mutex_unlock(me->lock);
    apr_thread_exit(t, APR_SUCCESS);
    return NULL;                /* should not be here, safe net */
}