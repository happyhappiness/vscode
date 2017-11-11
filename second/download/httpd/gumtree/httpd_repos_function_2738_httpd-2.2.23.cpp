static apr_status_t thread_pool_construct(apr_thread_pool_t * me,
                                          apr_size_t init_threads,
                                          apr_size_t max_threads)
{
    apr_status_t rv;
    int i;

    me->thd_max = max_threads;
    me->idle_max = init_threads;
    me->threshold = init_threads / 2;
    rv = apr_thread_mutex_create(&me->lock, APR_THREAD_MUTEX_NESTED,
                                 me->pool);
    if (APR_SUCCESS != rv) {
        return rv;
    }
    rv = apr_thread_cond_create(&me->cond, me->pool);
    if (APR_SUCCESS != rv) {
        apr_thread_mutex_destroy(me->lock);
        return rv;
    }
    me->tasks = apr_palloc(me->pool, sizeof(*me->tasks));
    if (!me->tasks) {
        goto CATCH_ENOMEM;
    }
    APR_RING_INIT(me->tasks, apr_thread_pool_task, link);
    me->scheduled_tasks = apr_palloc(me->pool, sizeof(*me->scheduled_tasks));
    if (!me->scheduled_tasks) {
        goto CATCH_ENOMEM;
    }
    APR_RING_INIT(me->scheduled_tasks, apr_thread_pool_task, link);
    me->recycled_tasks = apr_palloc(me->pool, sizeof(*me->recycled_tasks));
    if (!me->recycled_tasks) {
        goto CATCH_ENOMEM;
    }
    APR_RING_INIT(me->recycled_tasks, apr_thread_pool_task, link);
    me->busy_thds = apr_palloc(me->pool, sizeof(*me->busy_thds));
    if (!me->busy_thds) {
        goto CATCH_ENOMEM;
    }
    APR_RING_INIT(me->busy_thds, apr_thread_list_elt, link);
    me->idle_thds = apr_palloc(me->pool, sizeof(*me->idle_thds));
    if (!me->idle_thds) {
        goto CATCH_ENOMEM;
    }
    APR_RING_INIT(me->idle_thds, apr_thread_list_elt, link);
    me->recycled_thds = apr_palloc(me->pool, sizeof(*me->recycled_thds));
    if (!me->recycled_thds) {
        goto CATCH_ENOMEM;
    }
    APR_RING_INIT(me->recycled_thds, apr_thread_list_elt, link);
    me->thd_cnt = me->idle_cnt = me->task_cnt = me->scheduled_task_cnt = 0;
    me->tasks_run = me->tasks_high = me->thd_high = me->thd_timed_out = 0;
    me->idle_wait = 0;
    me->terminated = 0;
    for (i = 0; i < TASK_PRIORITY_SEGS; i++) {
        me->task_idx[i] = NULL;
    }
    goto FINAL_EXIT;
  CATCH_ENOMEM:
    rv = APR_ENOMEM;
    apr_thread_mutex_destroy(me->lock);
    apr_thread_cond_destroy(me->cond);
  FINAL_EXIT:
    return rv;
}