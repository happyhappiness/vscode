static int check_patch_list(struct apply_state *state, struct patch *patch)
{
	int err = 0;

	prepare_symlink_changes(state, patch);
	prepare_fn_table(state, patch);
	while (patch) {
		if (state->apply_verbosely)
			say_patch_name(stderr,
				       _("Checking patch %s..."), patch);
		err |= check_patch(state, patch);
		patch = patch->next;
	}
	return err;
}