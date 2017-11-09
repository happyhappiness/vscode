static void prefix_patch(struct apply_state *state, struct patch *p)
{
	if (!state->prefix || p->is_toplevel_relative)
		return;
	prefix_one(state, &p->new_name);
	prefix_one(state, &p->old_name);
}