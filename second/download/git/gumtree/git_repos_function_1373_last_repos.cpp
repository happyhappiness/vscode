static void prefix_one(struct apply_state *state, char **name)
{
	char *old_name = *name;
	if (!old_name)
		return;
	*name = prefix_filename(state->prefix, *name);
	free(old_name);
}