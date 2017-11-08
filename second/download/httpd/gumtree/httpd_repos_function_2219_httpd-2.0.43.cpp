static apr_status_t worker_stack_wait(worker_stack *stack,
                                      apr_uint32_t worker_id)
{
    worker_wakeup_info *wakeup = worker_wakeups[worker_id];

    while (1) {
        apr_uint32_t state = stack->state;
        if (state & (STACK_TERMINATED | STACK_NO_LISTENER)) {
            if (state & STACK_TERMINATED) {
                return APR_EINVAL;
            }
            if (apr_atomic_cas(&(stack->state), STACK_LIST_END, state) !=
                state) {
                continue;
            }
            else {
                return APR_SUCCESS;
            }
        }
        wakeup->next = state;
        if (apr_atomic_cas(&(stack->state), worker_id, state) != state) {
            continue;
        }
        else {
            return apr_thread_cond_wait(wakeup->cond, wakeup->mutex);
        }
    }    
}