static int prepare_to_commit(const char *index_file, const char *prefix,
			     struct commit *current_head,
			     struct wt_status *s,
			     struct strbuf *author_ident)
{
	struct stat statbuf;
	struct strbuf committer_ident = STRBUF_INIT;
	int commitable;
	struct strbuf sb = STRBUF_INIT;
	const char *hook_arg1 = NULL;
	const char *hook_arg2 = NULL;
	int clean_message_contents = (cleanup_mode != CLEANUP_NONE);
	int old_display_comment_prefix;

	/* This checks and barfs if author is badly specified */
	determine_author_info(author_ident);

	if (!no_verify && run_commit_hook(use_editor, index_file, "pre-commit", NULL))
		return 0;

	if (squash_message) {
		/*
		 * Insert the proper subject line before other commit
		 * message options add their content.
		 */
		if (use_message && !strcmp(use_message, squash_message))
			strbuf_addstr(&sb, "squash! ");
		else {
			struct pretty_print_context ctx = {0};
			struct commit *c;
			c = lookup_commit_reference_by_name(squash_message);
			if (!c)
				die(_("could not lookup commit %s"), squash_message);
			ctx.output_encoding = get_commit_output_encoding();
			format_commit_message(c, "squash! %s\n\n", &sb,
					      &ctx);
		}
	}

	if (have_option_m) {
		strbuf_addbuf(&sb, &message);
		hook_arg1 = "message";
	} else if (logfile && !strcmp(logfile, "-")) {
		if (isatty(0))
			fprintf(stderr, _("(reading log message from standard input)\n"));
		if (strbuf_read(&sb, 0, 0) < 0)
			die_errno(_("could not read log from standard input"));
		hook_arg1 = "message";
	} else if (logfile) {
		if (strbuf_read_file(&sb, logfile, 0) < 0)
			die_errno(_("could not read log file '%s'"),
				  logfile);
		hook_arg1 = "message";
	} else if (use_message) {
		char *buffer;
		buffer = strstr(use_message_buffer, "\n\n");
		if (buffer)
			strbuf_addstr(&sb, skip_blank_lines(buffer + 2));
		hook_arg1 = "commit";
		hook_arg2 = use_message;
	} else if (fixup_message) {
		struct pretty_print_context ctx = {0};
		struct commit *commit;
		commit = lookup_commit_reference_by_name(fixup_message);
		if (!commit)
			die(_("could not lookup commit %s"), fixup_message);
		ctx.output_encoding = get_commit_output_encoding();
		format_commit_message(commit, "fixup! %s\n\n",
				      &sb, &ctx);
		hook_arg1 = "message";
	} else if (!stat(git_path_merge_msg(), &statbuf)) {
		/*
		 * prepend SQUASH_MSG here if it exists and a
		 * "merge --squash" was originally performed
		 */
		if (!stat(git_path_squash_msg(), &statbuf)) {
			if (strbuf_read_file(&sb, git_path_squash_msg(), 0) < 0)
				die_errno(_("could not read SQUASH_MSG"));
			hook_arg1 = "squash";
		} else
			hook_arg1 = "merge";
		if (strbuf_read_file(&sb, git_path_merge_msg(), 0) < 0)
			die_errno(_("could not read MERGE_MSG"));
	} else if (!stat(git_path_squash_msg(), &statbuf)) {
		if (strbuf_read_file(&sb, git_path_squash_msg(), 0) < 0)
			die_errno(_("could not read SQUASH_MSG"));
		hook_arg1 = "squash";
	} else if (template_file) {
		if (strbuf_read_file(&sb, template_file, 0) < 0)
			die_errno(_("could not read '%s'"), template_file);
		hook_arg1 = "template";
		clean_message_contents = 0;
	}

	/*
	 * The remaining cases don't modify the template message, but
	 * just set the argument(s) to the prepare-commit-msg hook.
	 */
	else if (whence == FROM_MERGE)
		hook_arg1 = "merge";
	else if (whence == FROM_CHERRY_PICK) {
		hook_arg1 = "commit";
		hook_arg2 = "CHERRY_PICK_HEAD";
	}

	if (squash_message) {
		/*
		 * If squash_commit was used for the commit subject,
		 * then we're possibly hijacking other commit log options.
		 * Reset the hook args to tell the real story.
		 */
		hook_arg1 = "message";
		hook_arg2 = "";
	}

	s->fp = fopen_for_writing(git_path_commit_editmsg());
	if (s->fp == NULL)
		die_errno(_("could not open '%s'"), git_path_commit_editmsg());

	/* Ignore status.displayCommentPrefix: we do need comments in COMMIT_EDITMSG. */
	old_display_comment_prefix = s->display_comment_prefix;
	s->display_comment_prefix = 1;

	/*
	 * Most hints are counter-productive when the commit has
	 * already started.
	 */
	s->hints = 0;

	if (clean_message_contents)
		strbuf_stripspace(&sb, 0);

	if (signoff)
		append_signoff(&sb, ignore_non_trailer(sb.buf, sb.len), 0);

	if (fwrite(sb.buf, 1, sb.len, s->fp) < sb.len)
		die_errno(_("could not write commit template"));

	if (auto_comment_line_char)
		adjust_comment_line_char(&sb);
	strbuf_release(&sb);

	/* This checks if committer ident is explicitly given */
	strbuf_addstr(&committer_ident, git_committer_info(IDENT_STRICT));
	if (use_editor && include_status) {
		int ident_shown = 0;
		int saved_color_setting;
		struct ident_split ci, ai;

		if (whence != FROM_COMMIT) {
			if (cleanup_mode == CLEANUP_SCISSORS)
				wt_status_add_cut_line(s->fp);
			status_printf_ln(s, GIT_COLOR_NORMAL,
			    whence == FROM_MERGE
				? _("\n"
					"It looks like you may be committing a merge.\n"
					"If this is not correct, please remove the file\n"
					"	%s\n"
					"and try again.\n")
				: _("\n"
					"It looks like you may be committing a cherry-pick.\n"
					"If this is not correct, please remove the file\n"
					"	%s\n"
					"and try again.\n"),
				whence == FROM_MERGE ?
					git_path_merge_head() :
					git_path_cherry_pick_head());
		}

		fprintf(s->fp, "\n");
		if (cleanup_mode == CLEANUP_ALL)
			status_printf(s, GIT_COLOR_NORMAL,
				_("Please enter the commit message for your changes."
				  " Lines starting\nwith '%c' will be ignored, and an empty"
				  " message aborts the commit.\n"), comment_line_char);
		else if (cleanup_mode == CLEANUP_SCISSORS && whence == FROM_COMMIT)
			wt_status_add_cut_line(s->fp);
		else /* CLEANUP_SPACE, that is. */
			status_printf(s, GIT_COLOR_NORMAL,
				_("Please enter the commit message for your changes."
				  " Lines starting\n"
				  "with '%c' will be kept; you may remove them"
				  " yourself if you want to.\n"
				  "An empty message aborts the commit.\n"), comment_line_char);
		if (only_include_assumed)
			status_printf_ln(s, GIT_COLOR_NORMAL,
					"%s", only_include_assumed);

		/*
		 * These should never fail because they come from our own
		 * fmt_ident. They may fail the sane_ident test, but we know
		 * that the name and mail pointers will at least be valid,
		 * which is enough for our tests and printing here.
		 */
		assert_split_ident(&ai, author_ident);
		assert_split_ident(&ci, &committer_ident);

		if (ident_cmp(&ai, &ci))
			status_printf_ln(s, GIT_COLOR_NORMAL,
				_("%s"
				"Author:    %.*s <%.*s>"),
				ident_shown++ ? "" : "\n",
				(int)(ai.name_end - ai.name_begin), ai.name_begin,
				(int)(ai.mail_end - ai.mail_begin), ai.mail_begin);

		if (author_date_is_interesting())
			status_printf_ln(s, GIT_COLOR_NORMAL,
				_("%s"
				"Date:      %s"),
				ident_shown++ ? "" : "\n",
				show_ident_date(&ai, DATE_MODE(NORMAL)));

		if (!committer_ident_sufficiently_given())
			status_printf_ln(s, GIT_COLOR_NORMAL,
				_("%s"
				"Committer: %.*s <%.*s>"),
				ident_shown++ ? "" : "\n",
				(int)(ci.name_end - ci.name_begin), ci.name_begin,
				(int)(ci.mail_end - ci.mail_begin), ci.mail_begin);

		if (ident_shown)
			status_printf_ln(s, GIT_COLOR_NORMAL, "%s", "");

		saved_color_setting = s->use_color;
		s->use_color = 0;
		commitable = run_status(s->fp, index_file, prefix, 1, s);
		s->use_color = saved_color_setting;
	} else {
		struct object_id oid;
		const char *parent = "HEAD";

		if (!active_nr && read_cache() < 0)
			die(_("Cannot read index"));

		if (amend)
			parent = "HEAD^1";

		if (get_sha1(parent, oid.hash)) {
			int i, ita_nr = 0;

			for (i = 0; i < active_nr; i++)
				if (ce_intent_to_add(active_cache[i]))
					ita_nr++;
			commitable = active_nr - ita_nr > 0;
		} else {
			/*
			 * Unless the user did explicitly request a submodule
			 * ignore mode by passing a command line option we do
			 * not ignore any changed submodule SHA-1s when
			 * comparing index and parent, no matter what is
			 * configured. Otherwise we won't commit any
			 * submodules which were manually staged, which would
			 * be really confusing.
			 */
			int diff_flags = DIFF_OPT_OVERRIDE_SUBMODULE_CONFIG;
			if (ignore_submodule_arg &&
			    !strcmp(ignore_submodule_arg, "all"))
				diff_flags |= DIFF_OPT_IGNORE_SUBMODULES;
			commitable = index_differs_from(parent, diff_flags, 1);
		}
	}
	strbuf_release(&committer_ident);

	fclose(s->fp);

	/*
	 * Reject an attempt to record a non-merge empty commit without
	 * explicit --allow-empty. In the cherry-pick case, it may be
	 * empty due to conflict resolution, which the user should okay.
	 */
	if (!commitable && whence != FROM_MERGE && !allow_empty &&
	    !(amend && is_a_merge(current_head))) {
		s->display_comment_prefix = old_display_comment_prefix;
		run_status(stdout, index_file, prefix, 0, s);
		if (amend)
			fputs(_(empty_amend_advice), stderr);
		else if (whence == FROM_CHERRY_PICK) {
			fputs(_(empty_cherry_pick_advice), stderr);
			if (!sequencer_in_use)
				fputs(_(empty_cherry_pick_advice_single), stderr);
			else
				fputs(_(empty_cherry_pick_advice_multi), stderr);
		}
		return 0;
	}

	/*
	 * Re-read the index as pre-commit hook could have updated it,
	 * and write it out as a tree.  We must do this before we invoke
	 * the editor and after we invoke run_status above.
	 */
	discard_cache();
	read_cache_from(index_file);
	if (update_main_cache_tree(0)) {
		error(_("Error building trees"));
		return 0;
	}

	if (run_commit_hook(use_editor, index_file, "prepare-commit-msg",
			    git_path_commit_editmsg(), hook_arg1, hook_arg2, NULL))
		return 0;

	if (use_editor) {
		struct argv_array env = ARGV_ARRAY_INIT;

		argv_array_pushf(&env, "GIT_INDEX_FILE=%s", index_file);
		if (launch_editor(git_path_commit_editmsg(), NULL, env.argv)) {
			fprintf(stderr,
			_("Please supply the message using either -m or -F option.\n"));
			exit(1);
		}
		argv_array_clear(&env);
	}

	if (!no_verify &&
	    run_commit_hook(use_editor, index_file, "commit-msg", git_path_commit_editmsg(), NULL)) {
		return 0;
	}

	return 1;
}