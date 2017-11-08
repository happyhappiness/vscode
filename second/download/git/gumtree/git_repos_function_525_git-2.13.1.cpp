static void push_to_contains_stack(struct commit *candidate, struct contains_stack *contains_stack)
{
	ALLOC_GROW(contains_stack->contains_stack, contains_stack->nr + 1, contains_stack->alloc);
	contains_stack->contains_stack[contains_stack->nr].commit = candidate;
	contains_stack->contains_stack[contains_stack->nr++].parents = candidate->parents;
}