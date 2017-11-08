static apr_status_t worker_stack_terminate(worker_stack *stack)
{
    apr_status_t rv;
    worker_wakeup_info *worker;

    if ((rv = apr_thread_mutex_lock(stack->mutex)) != APR_SUCCESS) {
        return rv;
    }
    stack->terminated = 1;
    /* Wake up the listener thread. Although there will never be
     * more than one thread blocking on this condition, broadcast
     * just in case. */
    apr_thread_cond_broadcast(stack->cond);
    while (stack->nelts) {
        worker = stack->stack[--stack->nelts];
        apr_thread_mutex_lock(worker->mutex);
        worker->csd = 0;
        worker->state = WORKER_TERMINATED;
        apr_thread_cond_signal(worker->cond);
        apr_thread_mutex_unlock(worker->mutex);
    }
    if ((rv = apr_thread_mutex_unlock(stack->mutex)) != APR_SUCCESS) {
        return rv;
    }
    return APR_SUCCESS;
}