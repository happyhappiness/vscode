static void remove_file(struct apply_state *state, struct patch *patch, int rmdir_empty)
{
	if (state->update_index) {
		if (remove_file_from_cache(patch->old_name) < 0)
			die(_("unable to remove %s from index"), patch->old_name);
	}
	if (!state->cached) {
		if (!remove_or_warn(patch->old_mode, patch->old_name) && rmdir_empty) {
			remove_path(patch->old_name);
		}
	}
}