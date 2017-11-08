static apr_status_t worker_stack_awaken_next(worker_stack *stack)
{

    while (1) {
        apr_uint32_t state = stack->state;
        apr_uint32_t first = state & STACK_FIRST;
        if (first == STACK_LIST_END) {
            if (apr_atomic_cas(&(stack->state), state | STACK_NO_LISTENER,
                               state) != state) {
                continue;
            }
            else {
                return APR_SUCCESS;
            }
        }
        else {
            worker_wakeup_info *wakeup = worker_wakeups[first];
            if (apr_atomic_cas(&(stack->state), (state ^ first) | wakeup->next,
                               state) != state) {
                continue;
            }
            else {
                /* Acquire and release the idle worker's mutex to ensure
                 * that it's actually waiting on its condition variable
                 */
                apr_status_t rv;
                if ((rv = apr_thread_mutex_lock(wakeup->mutex)) !=
                    APR_SUCCESS) {
                    return rv;
                }
                if ((rv = apr_thread_mutex_unlock(wakeup->mutex)) !=
                    APR_SUCCESS) {
                    return rv;
                }
                return apr_thread_cond_signal(wakeup->cond);
            }
        }
    }
}