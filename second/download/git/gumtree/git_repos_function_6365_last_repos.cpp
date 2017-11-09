static int prune(int argc, const char **argv, const char *prefix)
{
	struct notes_tree *t;
	int show_only = 0, verbose = 0;
	struct option options[] = {
		OPT__DRY_RUN(&show_only, N_("do not remove, show only")),
		OPT__VERBOSE(&verbose, N_("report pruned notes")),
		OPT_END()
	};

	argc = parse_options(argc, argv, prefix, options, git_notes_prune_usage,
			     0);

	if (argc) {
		error(_("too many parameters"));
		usage_with_options(git_notes_prune_usage, options);
	}

	t = init_notes_check("prune", NOTES_INIT_WRITABLE);

	prune_notes(t, (verbose ? NOTES_PRUNE_VERBOSE : 0) |
		(show_only ? NOTES_PRUNE_VERBOSE|NOTES_PRUNE_DRYRUN : 0) );
	if (!show_only)
		commit_notes(t, "Notes removed by 'git notes prune'");
	free_notes(t);
	return 0;
}