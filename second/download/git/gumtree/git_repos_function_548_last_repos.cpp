static void push_stack_element(struct ref_formatting_stack **stack)
{
	struct ref_formatting_stack *s = xcalloc(1, sizeof(struct ref_formatting_stack));

	strbuf_init(&s->output, 0);
	s->prev = *stack;
	*stack = s;
}