static int parse_and_validate_options(int argc, const char *argv[],
				      const struct option *options,
				      const char * const usage[],
				      const char *prefix,
				      struct commit *current_head,
				      struct wt_status *s)
{
	int f = 0;

	argc = parse_options(argc, argv, prefix, options, usage, 0);
	finalize_deferred_config(s);

	if (force_author && !strchr(force_author, '>'))
		force_author = find_author_by_nickname(force_author);

	if (force_author && renew_authorship)
		die(_("Using both --reset-author and --author does not make sense"));

	if (logfile || have_option_m || use_message || fixup_message)
		use_editor = 0;
	if (0 <= edit_flag)
		use_editor = edit_flag;

	/* Sanity check options */
	if (amend && !current_head)
		die(_("You have nothing to amend."));
	if (amend && whence != FROM_COMMIT) {
		if (whence == FROM_MERGE)
			die(_("You are in the middle of a merge -- cannot amend."));
		else if (whence == FROM_CHERRY_PICK)
			die(_("You are in the middle of a cherry-pick -- cannot amend."));
	}
	if (fixup_message && squash_message)
		die(_("Options --squash and --fixup cannot be used together"));
	if (use_message)
		f++;
	if (edit_message)
		f++;
	if (fixup_message)
		f++;
	if (logfile)
		f++;
	if (f > 1)
		die(_("Only one of -c/-C/-F/--fixup can be used."));
	if (have_option_m && f > 0)
		die((_("Option -m cannot be combined with -c/-C/-F/--fixup.")));
	if (f || have_option_m)
		template_file = NULL;
	if (edit_message)
		use_message = edit_message;
	if (amend && !use_message && !fixup_message)
		use_message = "HEAD";
	if (!use_message && whence != FROM_CHERRY_PICK && renew_authorship)
		die(_("--reset-author can be used only with -C, -c or --amend."));
	if (use_message) {
		use_message_buffer = read_commit_message(use_message);
		if (!renew_authorship) {
			author_message = use_message;
			author_message_buffer = use_message_buffer;
		}
	}
	if (whence == FROM_CHERRY_PICK && !renew_authorship) {
		author_message = "CHERRY_PICK_HEAD";
		author_message_buffer = read_commit_message(author_message);
	}

	if (patch_interactive)
		interactive = 1;

	if (also + only + all + interactive > 1)
		die(_("Only one of --include/--only/--all/--interactive/--patch can be used."));
	if (argc == 0 && (also || (only && !amend && !allow_empty)))
		die(_("No paths with --include/--only does not make sense."));
	if (!cleanup_arg || !strcmp(cleanup_arg, "default"))
		cleanup_mode = use_editor ? CLEANUP_ALL : CLEANUP_SPACE;
	else if (!strcmp(cleanup_arg, "verbatim"))
		cleanup_mode = CLEANUP_NONE;
	else if (!strcmp(cleanup_arg, "whitespace"))
		cleanup_mode = CLEANUP_SPACE;
	else if (!strcmp(cleanup_arg, "strip"))
		cleanup_mode = CLEANUP_ALL;
	else if (!strcmp(cleanup_arg, "scissors"))
		cleanup_mode = use_editor ? CLEANUP_SCISSORS : CLEANUP_SPACE;
	else
		die(_("Invalid cleanup mode %s"), cleanup_arg);

	handle_untracked_files_arg(s);

	if (all && argc > 0)
		die(_("Paths with -a does not make sense."));

	if (status_format != STATUS_FORMAT_NONE)
		dry_run = 1;

	return argc;
}