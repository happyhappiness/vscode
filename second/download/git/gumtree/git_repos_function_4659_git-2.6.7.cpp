static int check_patch_list(struct patch *patch)
{
	int err = 0;

	prepare_symlink_changes(patch);
	prepare_fn_table(patch);
	while (patch) {
		if (apply_verbosely)
			say_patch_name(stderr,
				       _("Checking patch %s..."), patch);
		err |= check_patch(patch);
		patch = patch->next;
	}
	return err;
}