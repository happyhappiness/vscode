static int check_preimage(struct apply_state *state,
			  struct patch *patch,
			  struct cache_entry **ce,
			  struct stat *st)
{
	const char *old_name = patch->old_name;
	struct patch *previous = NULL;
	int stat_ret = 0, status;
	unsigned st_mode = 0;

	if (!old_name)
		return 0;

	assert(patch->is_new <= 0);
	previous = previous_patch(state, patch, &status);

	if (status)
		return error(_("path %s has been renamed/deleted"), old_name);
	if (previous) {
		st_mode = previous->new_mode;
	} else if (!state->cached) {
		stat_ret = lstat(old_name, st);
		if (stat_ret && errno != ENOENT)
			return error(_("%s: %s"), old_name, strerror(errno));
	}

	if (state->check_index && !previous) {
		int pos = cache_name_pos(old_name, strlen(old_name));
		if (pos < 0) {
			if (patch->is_new < 0)
				goto is_new;
			return error(_("%s: does not exist in index"), old_name);
		}
		*ce = active_cache[pos];
		if (stat_ret < 0) {
			if (checkout_target(&the_index, *ce, st))
				return -1;
		}
		if (!state->cached && verify_index_match(*ce, st))
			return error(_("%s: does not match index"), old_name);
		if (state->cached)
			st_mode = (*ce)->ce_mode;
	} else if (stat_ret < 0) {
		if (patch->is_new < 0)
			goto is_new;
		return error(_("%s: %s"), old_name, strerror(errno));
	}

	if (!state->cached && !previous)
		st_mode = ce_mode_from_stat(*ce, st->st_mode);

	if (patch->is_new < 0)
		patch->is_new = 0;
	if (!patch->old_mode)
		patch->old_mode = st_mode;
	if ((st_mode ^ patch->old_mode) & S_IFMT)
		return error(_("%s: wrong type"), old_name);
	if (st_mode != patch->old_mode)
		warning(_("%s has type %o, expected %o"),
			old_name, st_mode, patch->old_mode);
	if (!patch->new_mode && !patch->is_delete)
		patch->new_mode = st_mode;
	return 0;

 is_new:
	patch->is_new = 1;
	patch->is_delete = 0;
	free(patch->old_name);
	patch->old_name = NULL;
	return 0;
}