static void if_atom_handler(struct atom_value *atomv, struct ref_formatting_state *state)
{
	struct ref_formatting_stack *new;
	struct if_then_else *if_then_else = xcalloc(sizeof(struct if_then_else), 1);

	if_then_else->str = atomv->atom->u.if_then_else.str;
	if_then_else->cmp_status = atomv->atom->u.if_then_else.cmp_status;

	push_stack_element(&state->stack);
	new = state->stack;
	new->at_end = if_then_else_handler;
	new->at_end_data = if_then_else;
}