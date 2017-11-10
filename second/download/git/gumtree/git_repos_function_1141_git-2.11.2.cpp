void clear_apply_state(struct apply_state *state)
{
	string_list_clear(&state->limit_by_name, 0);
	string_list_clear(&state->symlink_changes, 0);
	strbuf_release(&state->root);

	/* &state->fn_table is cleared at the end of apply_patch() */
}