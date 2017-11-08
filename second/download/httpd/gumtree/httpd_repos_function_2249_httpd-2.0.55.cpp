static apr_status_t worker_stack_pop(worker_stack *stack,
                                     worker_wakeup_info **worker)
{
    apr_status_t rv;
    if ((rv = apr_thread_mutex_lock(stack->mutex)) != APR_SUCCESS) {
        return rv;
    }
    AP_DEBUG_ASSERT(stack->nelts >= 0);
    while ((stack->nelts == 0) && (!stack->terminated)) {
        rv = apr_thread_cond_wait(stack->cond, stack->mutex);
        if (rv != APR_SUCCESS) {
            apr_status_t rv2;
            rv2 = apr_thread_mutex_unlock(stack->mutex);
            if (rv2 != APR_SUCCESS) {
                return rv2;
            }
            return rv;
        }
    }
    if (stack->terminated) {
        if ((rv = apr_thread_mutex_unlock(stack->mutex)) != APR_SUCCESS) {
            return rv;
        }
        return APR_EOF;
    }
    *worker = stack->stack[--stack->nelts];
    if ((rv = apr_thread_mutex_unlock(stack->mutex)) != APR_SUCCESS) {
        return rv;
    }
    return APR_SUCCESS;
}