int cmd_add(int argc, const char **argv, const char *prefix)
{
	int exit_status = 0;
	struct pathspec pathspec;
	struct dir_struct dir;
	int flags, force_mode;
	int add_new_files;
	int require_pathspec;
	char *seen = NULL;

	git_config(add_config, NULL);

	argc = parse_options(argc, argv, prefix, builtin_add_options,
			  builtin_add_usage, PARSE_OPT_KEEP_ARGV0);
	if (patch_interactive)
		add_interactive = 1;
	if (add_interactive)
		exit(interactive_add(argc - 1, argv + 1, prefix, patch_interactive));

	if (edit_interactive)
		return(edit_patch(argc, argv, prefix));
	argc--;
	argv++;

	if (0 <= addremove_explicit)
		addremove = addremove_explicit;
	else if (take_worktree_changes && ADDREMOVE_DEFAULT)
		addremove = 0; /* "-u" was given but not "-A" */

	if (addremove && take_worktree_changes)
		die(_("-A and -u are mutually incompatible"));

	if (!take_worktree_changes && addremove_explicit < 0 && argc)
		/* Turn "git add pathspec..." to "git add -A pathspec..." */
		addremove = 1;

	if (!show_only && ignore_missing)
		die(_("Option --ignore-missing can only be used together with --dry-run"));

	if (!chmod_arg)
		force_mode = 0;
	else if (!strcmp(chmod_arg, "-x"))
		force_mode = 0666;
	else if (!strcmp(chmod_arg, "+x"))
		force_mode = 0777;
	else
		die(_("--chmod param '%s' must be either -x or +x"), chmod_arg);

	add_new_files = !take_worktree_changes && !refresh_only;
	require_pathspec = !(take_worktree_changes || (0 < addremove_explicit));

	hold_locked_index(&lock_file, 1);

	flags = ((verbose ? ADD_CACHE_VERBOSE : 0) |
		 (show_only ? ADD_CACHE_PRETEND : 0) |
		 (intent_to_add ? ADD_CACHE_INTENT : 0) |
		 (ignore_add_errors ? ADD_CACHE_IGNORE_ERRORS : 0) |
		 (!(addremove || take_worktree_changes)
		  ? ADD_CACHE_IGNORE_REMOVAL : 0));

	if (require_pathspec && argc == 0) {
		fprintf(stderr, _("Nothing specified, nothing added.\n"));
		fprintf(stderr, _("Maybe you wanted to say 'git add .'?\n"));
		return 0;
	}

	if (read_cache() < 0)
		die(_("index file corrupt"));

	/*
	 * Check the "pathspec '%s' did not match any files" block
	 * below before enabling new magic.
	 */
	parse_pathspec(&pathspec, 0,
		       PATHSPEC_PREFER_FULL |
		       PATHSPEC_SYMLINK_LEADING_PATH |
		       PATHSPEC_STRIP_SUBMODULE_SLASH_EXPENSIVE,
		       prefix, argv);

	if (add_new_files) {
		int baselen;

		/* Set up the default git porcelain excludes */
		memset(&dir, 0, sizeof(dir));
		if (!ignored_too) {
			dir.flags |= DIR_COLLECT_IGNORED;
			setup_standard_excludes(&dir);
		}

		/* This picks up the paths that are not tracked */
		baselen = fill_directory(&dir, &pathspec);
		if (pathspec.nr)
			seen = prune_directory(&dir, &pathspec, baselen);
	}

	if (refresh_only) {
		refresh(verbose, &pathspec);
		goto finish;
	}

	if (pathspec.nr) {
		int i;

		if (!seen)
			seen = find_pathspecs_matching_against_index(&pathspec);

		/*
		 * file_exists() assumes exact match
		 */
		GUARD_PATHSPEC(&pathspec,
			       PATHSPEC_FROMTOP |
			       PATHSPEC_LITERAL |
			       PATHSPEC_GLOB |
			       PATHSPEC_ICASE |
			       PATHSPEC_EXCLUDE);

		for (i = 0; i < pathspec.nr; i++) {
			const char *path = pathspec.items[i].match;
			if (pathspec.items[i].magic & PATHSPEC_EXCLUDE)
				continue;
			if (!seen[i] && path[0] &&
			    ((pathspec.items[i].magic &
			      (PATHSPEC_GLOB | PATHSPEC_ICASE)) ||
			     !file_exists(path))) {
				if (ignore_missing) {
					int dtype = DT_UNKNOWN;
					if (is_excluded(&dir, path, &dtype))
						dir_add_ignored(&dir, path, pathspec.items[i].len);
				} else
					die(_("pathspec '%s' did not match any files"),
					    pathspec.items[i].original);
			}
		}
		free(seen);
	}

	plug_bulk_checkin();

	exit_status |= add_files_to_cache(prefix, &pathspec, flags, force_mode);

	if (add_new_files)
		exit_status |= add_files(&dir, flags, force_mode);

	unplug_bulk_checkin();

finish:
	if (active_cache_changed) {
		if (write_locked_index(&the_index, &lock_file, COMMIT_LOCK))
			die(_("Unable to write new index file"));
	}

	return exit_status;
}