static worker_stack* worker_stack_create(apr_pool_t *pool, apr_size_t max)
{
    apr_status_t rv;
    worker_stack *stack = (worker_stack *)apr_palloc(pool, sizeof(*stack));

    if ((rv = apr_thread_mutex_create(&stack->mutex, APR_THREAD_MUTEX_DEFAULT,
                                      pool)) != APR_SUCCESS) {
        return NULL;
    }
    if ((rv = apr_thread_cond_create(&stack->cond, pool)) != APR_SUCCESS) {
        return NULL;
    }
    stack->nelts = 0;
    stack->nalloc = max;
    stack->stack =
        (worker_wakeup_info **)apr_palloc(pool, stack->nalloc *
                                          sizeof(worker_wakeup_info *));
    stack->terminated = 0;
    return stack;
}