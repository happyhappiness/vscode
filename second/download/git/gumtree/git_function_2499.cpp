static void end_atom_handler(struct atom_value *atomv, struct ref_formatting_state *state)
{
	struct ref_formatting_stack *current = state->stack;
	struct strbuf s = STRBUF_INIT;

	if (!current->at_end)
		die(_("format: %%(end) atom used without corresponding atom"));
	current->at_end(current);

	/*
	 * Perform quote formatting when the stack element is that of
	 * a supporting atom. If nested then perform quote formatting
	 * only on the topmost supporting atom.
	 */
	if (!state->stack->prev->prev) {
		quote_formatting(&s, current->output.buf, state->quote_style);
		strbuf_swap(&current->output, &s);
	}
	strbuf_release(&s);
	pop_stack_element(&state->stack);
}