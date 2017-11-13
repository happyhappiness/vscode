static void else_atom_handler(struct atom_value *atomv, struct ref_formatting_state *state)
{
	struct ref_formatting_stack *prev = state->stack;
	struct if_then_else *if_then_else = NULL;

	if (prev->at_end == if_then_else_handler)
		if_then_else = (struct if_then_else *)prev->at_end_data;
	if (!if_then_else)
		die(_("format: %%(else) atom used without an %%(if) atom"));
	if (!if_then_else->then_atom_seen)
		die(_("format: %%(else) atom used without a %%(then) atom"));
	if (if_then_else->else_atom_seen)
		die(_("format: %%(else) atom used more than once"));
	if_then_else->else_atom_seen = 1;
	push_stack_element(&state->stack);
	state->stack->at_end_data = prev->at_end_data;
	state->stack->at_end = prev->at_end;
}