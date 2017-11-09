static int guess_p_value(struct apply_state *state, const char *nameline)
{
	char *name, *cp;
	int val = -1;

	if (is_dev_null(nameline))
		return -1;
	name = find_name_traditional(state, nameline, NULL, 0);
	if (!name)
		return -1;
	cp = strchr(name, '/');
	if (!cp)
		val = 0;
	else if (state->prefix) {
		/*
		 * Does it begin with "a/$our-prefix" and such?  Then this is
		 * very likely to apply to our directory.
		 */
		if (starts_with(name, state->prefix))
			val = count_slashes(state->prefix);
		else {
			cp++;
			if (starts_with(cp, state->prefix))
				val = count_slashes(state->prefix) + 1;
		}
	}
	free(name);
	return val;
}