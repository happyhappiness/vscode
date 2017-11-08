static void align_atom_handler(struct atom_value *atomv, struct ref_formatting_state *state)
{
	struct ref_formatting_stack *new;

	push_stack_element(&state->stack);
	new = state->stack;
	new->at_end = end_align_handler;
	new->at_end_data = &atomv->atom->u.align;
}