	git_config(git_default_config, NULL);

	argc = parse_options(argc, argv, prefix, options, git_reset_usage,
						PARSE_OPT_KEEP_DASHDASH);
	parse_args(&pathspec, argv, prefix, patch_mode, &rev);

	unborn = !strcmp(rev, "HEAD") && get_sha1("HEAD", sha1);
	if (unborn) {
		/* reset on unborn branch: treat as reset to empty tree */
		hashcpy(sha1, EMPTY_TREE_SHA1_BIN);
	} else if (!pathspec.nr) {
		struct commit *commit;
		if (get_sha1_committish(rev, sha1))
			die(_("Failed to resolve '%s' as a valid revision."), rev);
		commit = lookup_commit_reference(sha1);
		if (!commit)
			die(_("Could not parse object '%s'."), rev);
		hashcpy(sha1, commit->object.sha1);
	} else {
		struct tree *tree;
		if (get_sha1_treeish(rev, sha1))
			die(_("Failed to resolve '%s' as a valid tree."), rev);
		tree = parse_tree_indirect(sha1);
		if (!tree)
			die(_("Could not parse object '%s'."), rev);
		hashcpy(sha1, tree->object.sha1);
	}

	if (patch_mode) {
		if (reset_type != NONE)
			die(_("--patch is incompatible with --{hard,mixed,soft}"));
		return run_add_interactive(rev, "--patch=reset", &pathspec);
