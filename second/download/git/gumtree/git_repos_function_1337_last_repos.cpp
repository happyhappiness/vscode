static int parse_traditional_patch(struct apply_state *state,
				   const char *first,
				   const char *second,
				   struct patch *patch)
{
	char *name;

	first += 4;	/* skip "--- " */
	second += 4;	/* skip "+++ " */
	if (!state->p_value_known) {
		int p, q;
		p = guess_p_value(state, first);
		q = guess_p_value(state, second);
		if (p < 0) p = q;
		if (0 <= p && p == q) {
			state->p_value = p;
			state->p_value_known = 1;
		}
	}
	if (is_dev_null(first)) {
		patch->is_new = 1;
		patch->is_delete = 0;
		name = find_name_traditional(state, second, NULL, state->p_value);
		patch->new_name = name;
	} else if (is_dev_null(second)) {
		patch->is_new = 0;
		patch->is_delete = 1;
		name = find_name_traditional(state, first, NULL, state->p_value);
		patch->old_name = name;
	} else {
		char *first_name;
		first_name = find_name_traditional(state, first, NULL, state->p_value);
		name = find_name_traditional(state, second, first_name, state->p_value);
		free(first_name);
		if (has_epoch_timestamp(first)) {
			patch->is_new = 1;
			patch->is_delete = 0;
			patch->new_name = name;
		} else if (has_epoch_timestamp(second)) {
			patch->is_new = 0;
			patch->is_delete = 1;
			patch->old_name = name;
		} else {
			patch->old_name = name;
			patch->new_name = xstrdup_or_null(name);
		}
	}
	if (!name)
		return error(_("unable to find filename in patch at line %d"), state->linenr);

	return 0;
}