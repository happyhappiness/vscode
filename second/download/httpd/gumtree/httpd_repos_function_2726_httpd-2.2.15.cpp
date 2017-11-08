static apr_interval_time_t waiting_time(apr_thread_pool_t * me)
{
    apr_thread_pool_task_t *task = NULL;

    task = APR_RING_FIRST(me->scheduled_tasks);
    assert(task != NULL);
    assert(task !=
           APR_RING_SENTINEL(me->scheduled_tasks, apr_thread_pool_task,
                             link));
    return task->dispatch.time - apr_time_now();
}