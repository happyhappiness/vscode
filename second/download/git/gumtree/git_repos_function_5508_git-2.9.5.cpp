int cmd_reset(int argc, const char **argv, const char *prefix)
{
	int reset_type = NONE, update_ref_status = 0, quiet = 0;
	int patch_mode = 0, unborn;
	const char *rev;
	struct object_id oid;
	struct pathspec pathspec;
	int intent_to_add = 0;
	const struct option options[] = {
		OPT__QUIET(&quiet, N_("be quiet, only report errors")),
		OPT_SET_INT(0, "mixed", &reset_type,
						N_("reset HEAD and index"), MIXED),
		OPT_SET_INT(0, "soft", &reset_type, N_("reset only HEAD"), SOFT),
		OPT_SET_INT(0, "hard", &reset_type,
				N_("reset HEAD, index and working tree"), HARD),
		OPT_SET_INT(0, "merge", &reset_type,
				N_("reset HEAD, index and working tree"), MERGE),
		OPT_SET_INT(0, "keep", &reset_type,
				N_("reset HEAD but keep local changes"), KEEP),
		OPT_BOOL('p', "patch", &patch_mode, N_("select hunks interactively")),
		OPT_BOOL('N', "intent-to-add", &intent_to_add,
				N_("record only the fact that removed paths will be added later")),
		OPT_END()
	};

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
	}

	/* git reset tree [--] paths... can be used to
	 * load chosen paths from the tree into the index without
	 * affecting the working tree nor HEAD. */
	if (pathspec.nr) {
		if (reset_type == MIXED)
			warning(_("--mixed with paths is deprecated; use 'git reset -- <paths>' instead."));
		else if (reset_type != NONE)
			die(_("Cannot do %s reset with paths."),
					_(reset_type_names[reset_type]));
	}
	if (reset_type == NONE)
		reset_type = MIXED; /* by default */

	if (reset_type != SOFT && (reset_type != MIXED || get_git_work_tree()))
		setup_work_tree();

	if (reset_type == MIXED && is_bare_repository())
		die(_("%s reset is not allowed in a bare repository"),
		    _(reset_type_names[reset_type]));

	if (intent_to_add && reset_type != MIXED)
		die(_("-N can only be used with --mixed"));

	/* Soft reset does not touch the index file nor the working tree
	 * at all, but requires them in a good order.  Other resets reset
	 * the index file to the tree object we are switching to. */
	if (reset_type == SOFT || reset_type == KEEP)
		die_if_unmerged_cache(reset_type);

	if (reset_type != SOFT) {
		struct lock_file *lock = xcalloc(1, sizeof(*lock));
		hold_locked_index(lock, 1);
		if (reset_type == MIXED) {
			int flags = quiet ? REFRESH_QUIET : REFRESH_IN_PORCELAIN;
			if (read_from_tree(&pathspec, oid.hash, intent_to_add))
				return 1;
			if (get_git_work_tree())
				refresh_index(&the_index, flags, NULL, NULL,
					      _("Unstaged changes after reset:"));
		} else {
			int err = reset_index(oid.hash, reset_type, quiet);
			if (reset_type == KEEP && !err)
				err = reset_index(oid.hash, MIXED, quiet);
			if (err)
				die(_("Could not reset index file to revision '%s'."), rev);
		}

		if (write_locked_index(&the_index, lock, COMMIT_LOCK))
			die(_("Could not write new index file."));
	}

	if (!pathspec.nr && !unborn) {
		/* Any resets without paths update HEAD to the head being
		 * switched to, saving the previous head in ORIG_HEAD before. */
		update_ref_status = reset_refs(rev, oid.hash);

		if (reset_type == HARD && !update_ref_status && !quiet)
			print_new_head_line(lookup_commit_reference(oid.hash));
	}
	if (!pathspec.nr)
		remove_branch_state();

	return update_ref_status;
}