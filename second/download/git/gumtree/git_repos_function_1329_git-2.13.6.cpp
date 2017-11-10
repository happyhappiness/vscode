static int write_out_one_result(struct apply_state *state,
				struct patch *patch,
				int phase)
{
	if (patch->is_delete > 0) {
		if (phase == 0)
			return remove_file(state, patch, 1);
		return 0;
	}
	if (patch->is_new > 0 || patch->is_copy) {
		if (phase == 1)
			return create_file(state, patch);
		return 0;
	}
	/*
	 * Rename or modification boils down to the same
	 * thing: remove the old, write the new
	 */
	if (phase == 0)
		return remove_file(state, patch, patch->is_rename);
	if (phase == 1)
		return create_file(state, patch);
	return 0;
}