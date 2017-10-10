					       "match old mode (%o) of %s"),
					patch->new_mode, new_name,
					patch->old_mode, old_name);
		}
	}

	if (!unsafe_paths)
		die_on_unsafe_path(patch);

	/*
	 * An attempt to read from or delete a path that is beyond a
	 * symbolic link will be prevented by load_patch_target() that
	 * is called at the beginning of apply_data() so we do not
	 * have to worry about a patch marked with "is_delete" bit
	 * here.  We however need to make sure that the patch result
	 * is not deposited to a path that is beyond a symbolic link
	 * here.
	 */
	if (!patch->is_delete && path_is_beyond_symlink(patch->new_name))
		return error(_("affected file '%s' is beyond a symbolic link"),
			     patch->new_name);

	if (apply_data(patch, &st, ce) < 0)
		return error(_("%s: patch does not apply"), name);
	patch->rejected = 0;
	return 0;
}

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

/* This function tries to read the sha1 from the current index */
