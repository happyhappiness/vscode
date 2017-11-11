static void am_resolve(struct am_state *state)
{
	validate_resume_state(state);

	say(state, stdout, _("Applying: %.*s"), linelen(state->msg), state->msg);

	if (!index_has_changes(NULL)) {
		printf_ln(_("No changes - did you forget to use 'git add'?\n"
			"If there is nothing left to stage, chances are that something else\n"
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
			goto next;
	}

	rerere(0);

	do_commit(state);

next:
	am_next(state);
	am_load(state);
	am_run(state, 0);
}