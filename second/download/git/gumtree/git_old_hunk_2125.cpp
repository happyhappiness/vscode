					       "match old mode (%o) of %s"),
					patch->new_mode, new_name,
					patch->old_mode, old_name);
		}
	}

	if (apply_data(patch, &st, ce) < 0)
		return error(_("%s: patch does not apply"), name);
	patch->rejected = 0;
	return 0;
}

static int check_patch_list(struct patch *patch)
{
	int err = 0;

	prepare_fn_table(patch);
	while (patch) {
		if (apply_verbosely)
			say_patch_name(stderr,
				       _("Checking patch %s..."), patch);
		err |= check_patch(patch);
