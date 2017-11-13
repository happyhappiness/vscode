static void then_atom_handler(struct atom_value *atomv, struct ref_formatting_state *state)
{
	struct ref_formatting_stack *cur = state->stack;
	struct if_then_else *if_then_else = NULL;

	if (cur->at_end == if_then_else_handler)
		if_then_else = (struct if_then_else *)cur->at_end_data;
	if (!if_then_else)
		die(_("format: %%(then) atom used without an %%(if) atom"));
	if (if_then_else->then_atom_seen)
		die(_("format: %%(then) atom used more than once"));
	if (if_then_else->else_atom_seen)
		die(_("format: %%(then) atom used after %%(else)"));
	if_then_else->then_atom_seen = 1;
	/*
	 * If the 'equals' or 'notequals' attribute is used then
	 * perform the required comparison. If not, only non-empty
	 * strings satisfy the 'if' condition.
	 */
	if (if_then_else->cmp_status == COMPARE_EQUAL) {
		if (!strcmp(if_then_else->str, cur->output.buf))
			if_then_else->condition_satisfied = 1;
	} else if (if_then_else->cmp_status == COMPARE_UNEQUAL) {
		if (strcmp(if_then_else->str, cur->output.buf))
			if_then_else->condition_satisfied = 1;
	} else if (cur->output.len && !is_empty(cur->output.buf))
		if_then_else->condition_satisfied = 1;
	strbuf_reset(&cur->output);
}