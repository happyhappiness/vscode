static void am_run(struct am_state *state, int resume)
{
	const char *argv_gc_auto[] = {"gc", "--auto", NULL};
	struct strbuf sb = STRBUF_INIT;

	unlink(am_path(state, "dirtyindex"));

	refresh_and_write_cache();

	if (index_has_changes(&sb)) {
		write_state_bool(state, "dirtyindex", 1);
		die(_("Dirty index: cannot apply patches (dirty: %s)"), sb.buf);
	}

	strbuf_release(&sb);

	while (state->cur <= state->last) {
		const char *mail = am_path(state, msgnum(state));
		int apply_status;

		reset_ident_date();

		if (!file_exists(mail))
			goto next;

		if (resume) {
			validate_resume_state(state);
		} else {
			int skip;

			if (state->rebasing)
				skip = parse_mail_rebase(state, mail);
			else
				skip = parse_mail(state, mail);

			if (skip)
				goto next; /* mail should be skipped */

			write_author_script(state);
			write_commit_msg(state);
		}

		if (state->interactive && do_interactive(state))
			goto next;

		if (run_applypatch_msg_hook(state))
			exit(1);

		say(state, stdout, _("Applying: %.*s"), linelen(state->msg), state->msg);

		apply_status = run_apply(state, NULL);

		if (apply_status && state->threeway) {
			struct strbuf sb = STRBUF_INIT;

			strbuf_addstr(&sb, am_path(state, "patch-merge-index"));
			apply_status = fall_back_threeway(state, sb.buf);
			strbuf_release(&sb);

			/*
			 * Applying the patch to an earlier tree and merging
			 * the result may have produced the same tree as ours.
			 */
			if (!apply_status && !index_has_changes(NULL)) {
				say(state, stdout, _("No changes -- Patch already applied."));
				goto next;
			}
		}

		if (apply_status) {
			int advice_amworkdir = 1;

			printf_ln(_("Patch failed at %s %.*s"), msgnum(state),
				linelen(state->msg), state->msg);

			git_config_get_bool("advice.amworkdir", &advice_amworkdir);

			if (advice_amworkdir)
				printf_ln(_("The copy of the patch that failed is found in: %s"),
						am_path(state, "patch"));

			die_user_resolve(state);
		}

		do_commit(state);

next:
		am_next(state);

		if (resume)
			am_load(state);
		resume = 0;
	}

	if (!is_empty_file(am_path(state, "rewritten"))) {
		assert(state->rebasing);
		copy_notes_for_rebase(state);
		run_post_rewrite_hook(state);
	}

	/*
	 * In rebasing mode, it's up to the caller to take care of
	 * housekeeping.
	 */
	if (!state->rebasing) {
		am_destroy(state);
		close_all_packs();
		run_command_v_opt(argv_gc_auto, RUN_GIT_CMD);
	}
}