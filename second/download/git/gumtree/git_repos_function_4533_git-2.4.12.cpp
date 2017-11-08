int cmd_branch(int argc, const char **argv, const char *prefix)
{
	int delete = 0, rename = 0, force = 0, list = 0;
	int verbose = 0, abbrev = -1, detached = 0;
	int reflog = 0, edit_description = 0;
	int quiet = 0, unset_upstream = 0;
	const char *new_upstream = NULL;
	enum branch_track track;
	int kinds = REF_LOCAL_BRANCH;
	struct commit_list *with_commit = NULL;

	struct option options[] = {
		OPT_GROUP(N_("Generic options")),
		OPT__VERBOSE(&verbose,
			N_("show hash and subject, give twice for upstream branch")),
		OPT__QUIET(&quiet, N_("suppress informational messages")),
		OPT_SET_INT('t', "track",  &track, N_("set up tracking mode (see git-pull(1))"),
			BRANCH_TRACK_EXPLICIT),
		OPT_SET_INT( 0, "set-upstream",  &track, N_("change upstream info"),
			BRANCH_TRACK_OVERRIDE),
		OPT_STRING('u', "set-upstream-to", &new_upstream, "upstream", "change the upstream info"),
		OPT_BOOL(0, "unset-upstream", &unset_upstream, "Unset the upstream info"),
		OPT__COLOR(&branch_use_color, N_("use colored output")),
		OPT_SET_INT('r', "remotes",     &kinds, N_("act on remote-tracking branches"),
			REF_REMOTE_BRANCH),
		{
			OPTION_CALLBACK, 0, "contains", &with_commit, N_("commit"),
			N_("print only branches that contain the commit"),
			PARSE_OPT_LASTARG_DEFAULT,
			parse_opt_with_commit, (intptr_t)"HEAD",
		},
		{
			OPTION_CALLBACK, 0, "with", &with_commit, N_("commit"),
			N_("print only branches that contain the commit"),
			PARSE_OPT_HIDDEN | PARSE_OPT_LASTARG_DEFAULT,
			parse_opt_with_commit, (intptr_t) "HEAD",
		},
		OPT__ABBREV(&abbrev),

		OPT_GROUP(N_("Specific git-branch actions:")),
		OPT_SET_INT('a', "all", &kinds, N_("list both remote-tracking and local branches"),
			REF_REMOTE_BRANCH | REF_LOCAL_BRANCH),
		OPT_BIT('d', "delete", &delete, N_("delete fully merged branch"), 1),
		OPT_BIT('D', NULL, &delete, N_("delete branch (even if not merged)"), 2),
		OPT_BIT('m', "move", &rename, N_("move/rename a branch and its reflog"), 1),
		OPT_BIT('M', NULL, &rename, N_("move/rename a branch, even if target exists"), 2),
		OPT_BOOL(0, "list", &list, N_("list branch names")),
		OPT_BOOL('l', "create-reflog", &reflog, N_("create the branch's reflog")),
		OPT_BOOL(0, "edit-description", &edit_description,
			 N_("edit the description for the branch")),
		OPT__FORCE(&force, N_("force creation, move/rename, deletion")),
		{
			OPTION_CALLBACK, 0, "no-merged", &merge_filter_ref,
			N_("commit"), N_("print only not merged branches"),
			PARSE_OPT_LASTARG_DEFAULT | PARSE_OPT_NONEG,
			opt_parse_merge_filter, (intptr_t) "HEAD",
		},
		{
			OPTION_CALLBACK, 0, "merged", &merge_filter_ref,
			N_("commit"), N_("print only merged branches"),
			PARSE_OPT_LASTARG_DEFAULT | PARSE_OPT_NONEG,
			opt_parse_merge_filter, (intptr_t) "HEAD",
		},
		OPT_COLUMN(0, "column", &colopts, N_("list branches in columns")),
		OPT_END(),
	};

	if (argc == 2 && !strcmp(argv[1], "-h"))
		usage_with_options(builtin_branch_usage, options);

	git_config(git_branch_config, NULL);

	track = git_branch_track;

	head = resolve_refdup("HEAD", 0, head_sha1, NULL);
	if (!head)
		die(_("Failed to resolve HEAD as a valid ref."));
	if (!strcmp(head, "HEAD"))
		detached = 1;
	else if (!skip_prefix(head, "refs/heads/", &head))
		die(_("HEAD not found below refs/heads!"));
	hashcpy(merge_filter_ref, head_sha1);


	argc = parse_options(argc, argv, prefix, options, builtin_branch_usage,
			     0);

	if (!delete && !rename && !edit_description && !new_upstream && !unset_upstream && argc == 0)
		list = 1;

	if (with_commit || merge_filter != NO_FILTER)
		list = 1;

	if (!!delete + !!rename + !!new_upstream +
	    list + unset_upstream > 1)
		usage_with_options(builtin_branch_usage, options);

	if (abbrev == -1)
		abbrev = DEFAULT_ABBREV;
	finalize_colopts(&colopts, -1);
	if (verbose) {
		if (explicitly_enable_column(colopts))
			die(_("--column and --verbose are incompatible"));
		colopts = 0;
	}

	if (force) {
		delete *= 2;
		rename *= 2;
	}

	if (delete) {
		if (!argc)
			die(_("branch name required"));
		return delete_branches(argc, argv, delete > 1, kinds, quiet);
	} else if (list) {
		int ret = print_ref_list(kinds, detached, verbose, abbrev,
					 with_commit, argv);
		print_columns(&output, colopts, NULL);
		string_list_clear(&output, 0);
		return ret;
	}
	else if (edit_description) {
		const char *branch_name;
		struct strbuf branch_ref = STRBUF_INIT;

		if (!argc) {
			if (detached)
				die(_("Cannot give description to detached HEAD"));
			branch_name = head;
		} else if (argc == 1)
			branch_name = argv[0];
		else
			die(_("cannot edit description of more than one branch"));

		strbuf_addf(&branch_ref, "refs/heads/%s", branch_name);
		if (!ref_exists(branch_ref.buf)) {
			strbuf_release(&branch_ref);

			if (!argc)
				return error(_("No commit on branch '%s' yet."),
					     branch_name);
			else
				return error(_("No branch named '%s'."),
					     branch_name);
		}
		strbuf_release(&branch_ref);

		if (edit_branch_description(branch_name))
			return 1;
	} else if (rename) {
		if (!argc)
			die(_("branch name required"));
		else if (argc == 1)
			rename_branch(head, argv[0], rename > 1);
		else if (argc == 2)
			rename_branch(argv[0], argv[1], rename > 1);
		else
			die(_("too many branches for a rename operation"));
	} else if (new_upstream) {
		struct branch *branch = branch_get(argv[0]);

		if (argc > 1)
			die(_("too many branches to set new upstream"));

		if (!branch) {
			if (!argc || !strcmp(argv[0], "HEAD"))
				die(_("could not set upstream of HEAD to %s when "
				      "it does not point to any branch."),
				    new_upstream);
			die(_("no such branch '%s'"), argv[0]);
		}

		if (!ref_exists(branch->refname))
			die(_("branch '%s' does not exist"), branch->name);

		/*
		 * create_branch takes care of setting up the tracking
		 * info and making sure new_upstream is correct
		 */
		create_branch(head, branch->name, new_upstream, 0, 0, 0, quiet, BRANCH_TRACK_OVERRIDE);
	} else if (unset_upstream) {
		struct branch *branch = branch_get(argv[0]);
		struct strbuf buf = STRBUF_INIT;

		if (argc > 1)
			die(_("too many branches to unset upstream"));

		if (!branch) {
			if (!argc || !strcmp(argv[0], "HEAD"))
				die(_("could not unset upstream of HEAD when "
				      "it does not point to any branch."));
			die(_("no such branch '%s'"), argv[0]);
		}

		if (!branch_has_merge_config(branch))
			die(_("Branch '%s' has no upstream information"), branch->name);

		strbuf_addf(&buf, "branch.%s.remote", branch->name);
		git_config_set_multivar(buf.buf, NULL, NULL, 1);
		strbuf_reset(&buf);
		strbuf_addf(&buf, "branch.%s.merge", branch->name);
		git_config_set_multivar(buf.buf, NULL, NULL, 1);
		strbuf_release(&buf);
	} else if (argc > 0 && argc <= 2) {
		struct branch *branch = branch_get(argv[0]);
		int branch_existed = 0, remote_tracking = 0;
		struct strbuf buf = STRBUF_INIT;

		if (!strcmp(argv[0], "HEAD"))
			die(_("it does not make sense to create 'HEAD' manually"));

		if (!branch)
			die(_("no such branch '%s'"), argv[0]);

		if (kinds != REF_LOCAL_BRANCH)
			die(_("-a and -r options to 'git branch' do not make sense with a branch name"));

		if (track == BRANCH_TRACK_OVERRIDE)
			fprintf(stderr, _("The --set-upstream flag is deprecated and will be removed. Consider using --track or --set-upstream-to\n"));

		strbuf_addf(&buf, "refs/remotes/%s", branch->name);
		remote_tracking = ref_exists(buf.buf);
		strbuf_release(&buf);

		branch_existed = ref_exists(branch->refname);
		create_branch(head, argv[0], (argc == 2) ? argv[1] : head,
			      force, reflog, 0, quiet, track);

		/*
		 * We only show the instructions if the user gave us
		 * one branch which doesn't exist locally, but is the
		 * name of a remote-tracking branch.
		 */
		if (argc == 1 && track == BRANCH_TRACK_OVERRIDE &&
		    !branch_existed && remote_tracking) {
			fprintf(stderr, _("\nIf you wanted to make '%s' track '%s', do this:\n\n"), head, branch->name);
			fprintf(stderr, _("    git branch -d %s\n"), branch->name);
			fprintf(stderr, _("    git branch --set-upstream-to %s\n"), branch->name);
		}

	} else
		usage_with_options(builtin_branch_usage, options);

	return 0;
}