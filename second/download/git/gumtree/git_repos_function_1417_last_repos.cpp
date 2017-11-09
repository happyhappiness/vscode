static int check_patch_list(struct apply_state *state, struct patch *patch)
{
	int err = 0;

	prepare_symlink_changes(state, patch);
	prepare_fn_table(state, patch);
	while (patch) {
		int res;
		if (state->apply_verbosity > verbosity_normal)
			say_patch_name(stderr,
				       _("Checking patch %s..."), patch);
		res = check_patch(state, patch);
		if (res == -128)
			return -128;
		err |= res;
		patch = patch->next;
	}
	return err;
}