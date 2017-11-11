static apr_thread_pool_task_t *task_new(apr_thread_pool_t * me,
                                        apr_thread_start_t func,
                                        void *param, apr_byte_t priority,
                                        void *owner, apr_time_t time)
{
    apr_thread_pool_task_t *t;

    if (APR_RING_EMPTY(me->recycled_tasks, apr_thread_pool_task, link)) {
        t = apr_pcalloc(me->pool, sizeof(*t));
        if (NULL == t) {
            return NULL;
        }
    }
    else {
        t = APR_RING_FIRST(me->recycled_tasks);
        APR_RING_REMOVE(t, link);
    }

    APR_RING_ELEM_INIT(t, link);
    t->func = func;
    t->param = param;
    t->owner = owner;
    if (time > 0) {
        t->dispatch.time = apr_time_now() + time;
    }
    else {
        t->dispatch.priority = priority;
    }
    return t;
}