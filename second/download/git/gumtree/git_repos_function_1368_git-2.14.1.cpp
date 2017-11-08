static int use_patch(struct apply_state *state, struct patch *p)
{
	const char *pathname = p->new_name ? p->new_name : p->old_name;
	int i;

	/* Paths outside are not touched regardless of "--include" */
	if (0 < state->prefix_length) {
		int pathlen = strlen(pathname);
		if (pathlen <= state->prefix_length ||
		    memcmp(state->prefix, pathname, state->prefix_length))
			return 0;
	}

	/* See if it matches any of exclude/include rule */
	for (i = 0; i < state->limit_by_name.nr; i++) {
		struct string_list_item *it = &state->limit_by_name.items[i];
		if (!wildmatch(it->string, pathname, 0))
			return (it->util != NULL);
	}

	/*
	 * If we had any include, a path that does not match any rule is
	 * not used.  Otherwise, we saw bunch of exclude rules (or none)
	 * and such a path is used.
	 */
	return !state->has_include;
}