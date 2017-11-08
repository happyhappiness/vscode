static apr_status_t worker_stack_term(worker_stack *stack)
{
    int i;
    apr_status_t rv;

    while (1) {
        apr_uint32_t state = stack->state;
        if (apr_atomic_cas(&(stack->state), state | STACK_TERMINATED,
                           state) == state) {
            break;
        }
    }
    for (i = 0; i < ap_threads_per_child; i++) {
        if ((rv = worker_stack_awaken_next(stack)) != APR_SUCCESS) {
            return rv;
        }
    }
    return APR_SUCCESS;
}