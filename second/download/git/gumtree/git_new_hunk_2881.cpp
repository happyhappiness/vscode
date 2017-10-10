	git_config(git_default_config, NULL);

	argc = parse_options(argc, argv, prefix, options, git_reset_usage,
						PARSE_OPT_KEEP_DASHDASH);
	parse_args(&pathspec, argv, prefix, patch_mode, &rev);

	unborn = !strcmp(rev, "HEAD") && get_sha1("HEAD", oid.hash);
	if (unborn) {
		/* reset on unborn branch: treat as reset to empty tree */
		hashcpy(oid.hash, EMPTY_TREE_SHA1_BIN);
	} else if (!pathspec.nr) {
		struct commit *commit;
		if (get_sha1_committish(rev, oid.hash))
			die(_("Failed to resolve '%s' as a valid revision."), rev);
		commit = lookup_commit_reference(oid.hash);
		if (!commit)
			die(_("Could not parse object '%s'."), rev);
		oidcpy(&oid, &commit->object.oid);
	} else {
		struct tree *tree;
		if (get_sha1_treeish(rev, oid.hash))
			die(_("Failed to resolve '%s' as a valid tree."), rev);
		tree = parse_tree_indirect(oid.hash);
		if (!tree)
			die(_("Could not parse object '%s'."), rev);
		oidcpy(&oid, &tree->object.oid);
	}

	if (patch_mode) {
		if (reset_type != NONE)
			die(_("--patch is incompatible with --{hard,mixed,soft}"));
		return run_add_interactive(rev, "--patch=reset", &pathspec);
