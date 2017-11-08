static void push_to_stack(struct commit *candidate, struct stack *stack)
{
	int index = stack->nr++;
	ALLOC_GROW(stack->stack, stack->nr, stack->alloc);
	stack->stack[index].commit = candidate;
	stack->stack[index].parents = candidate->parents;
}