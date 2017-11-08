static worker_stack* worker_stack_create(apr_pool_t *pool, apr_size_t max)
{
    worker_stack *stack = (worker_stack *)apr_palloc(pool, sizeof(*stack));
    stack->state = STACK_NO_LISTENER | STACK_LIST_END;
    return stack;
}