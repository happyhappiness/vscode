static void prefix_one(struct apply_state *state, char **name)
{
	char *old_name = *name;
	if (!old_name)
		return;
	*name = xstrdup(prefix_filename(state->prefix, state->prefix_length, *name));
	free(old_name);
}