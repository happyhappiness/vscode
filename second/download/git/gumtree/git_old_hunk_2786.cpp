	return status;
}

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
