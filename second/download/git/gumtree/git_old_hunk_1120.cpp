			"already introduced the same changes; you might want to skip this patch."));
		die_user_resolve(state);
	}

	if (unmerged_cache()) {
		printf_ln(_("You still have unmerged paths in your index.\n"
			"Did you forget to use 'git add'?"));
		die_user_resolve(state);
	}

	if (state->interactive) {
		write_index_patch(state);
		if (do_interactive(state))
