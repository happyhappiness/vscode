		strbuf_addbuf(&prev->output, &current->output);
	strbuf_release(&current->output);
	free(current);
	*stack = prev;
}

static void end_align_handler(struct ref_formatting_stack *stack)
{
	struct align *align = (struct align *)stack->at_end_data;
	struct strbuf s = STRBUF_INIT;

	strbuf_utf8_align(&s, align->position, align->width, stack->output.buf);
	strbuf_swap(&stack->output, &s);
	strbuf_release(&s);
}

static void align_atom_handler(struct atom_value *atomv, struct ref_formatting_state *state)
{
	struct ref_formatting_stack *new;

	push_stack_element(&state->stack);
	new = state->stack;
	new->at_end = end_align_handler;
	new->at_end_data = &atomv->u.align;
}

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
