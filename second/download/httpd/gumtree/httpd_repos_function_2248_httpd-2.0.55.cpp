static apr_status_t worker_stack_wait(worker_stack *stack,
                                      worker_wakeup_info *wakeup)
{
    apr_status_t rv;

    wakeup->state = WORKER_IDLE;
    
    if ((rv = apr_thread_mutex_lock(stack->mutex)) != APR_SUCCESS) {
        return rv;
    }
    if (stack->terminated) {
        if ((rv = apr_thread_mutex_unlock(stack->mutex)) != APR_SUCCESS) {
            return rv;
        }
        return APR_EOF;
    }
    if (stack->nelts == stack->nalloc) {
        if ((rv = apr_thread_mutex_unlock(stack->mutex)) != APR_SUCCESS) {
            return rv;
        }
        return APR_ENOSPC;
    }
    stack->stack[stack->nelts] = wakeup;
    /* Signal a blocking listener thread only if we just made the
     * stack non-empty. */
    if (stack->nelts++ == 0) {
        (void)apr_thread_cond_signal(stack->cond);
    }
    if ((rv = apr_thread_mutex_unlock(stack->mutex)) != APR_SUCCESS) {
        return rv;
    }

    /* At this point we've already added this worker to the stack, now
     * we just wait until the listener has accept()ed a connection
     * for us. */
    if ((rv = apr_thread_mutex_lock(wakeup->mutex)) != APR_SUCCESS) {
        return rv;
    }
    while (wakeup->state == WORKER_IDLE) {
        if ((rv = apr_thread_cond_wait(wakeup->cond, wakeup->mutex)) !=
            APR_SUCCESS) {
            return rv;
        }
    }
    if ((rv = apr_thread_mutex_unlock(wakeup->mutex)) != APR_SUCCESS) {
        return rv;
    }
    return APR_SUCCESS;
}