			"already introduced the same changes; you might want to skip this patch."));
		die_user_resolve(state);
	}

	if (unmerged_cache()) {
		printf_ln(_("You still have unmerged paths in your index.\n"
			"You should 'git add' each file with resolved conflicts to mark them as such.\n"
			"You might run `git rm` on a file to accept \"deleted by them\" for it."));
		die_user_resolve(state);
	}

	if (state->interactive) {
		write_index_patch(state);
		if (do_interactive(state))
