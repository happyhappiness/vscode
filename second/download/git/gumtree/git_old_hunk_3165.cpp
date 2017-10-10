
	if (argc) {
		error(_("too many parameters"));
		usage_with_options(git_notes_prune_usage, options);
	}

	t = init_notes_check("prune");

	prune_notes(t, (verbose ? NOTES_PRUNE_VERBOSE : 0) |
		(show_only ? NOTES_PRUNE_VERBOSE|NOTES_PRUNE_DRYRUN : 0) );
	if (!show_only)
		commit_notes(t, "Notes removed by 'git notes prune'");
	free_notes(t);
