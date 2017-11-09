int cmd_mv(int argc, const char **argv, const char *prefix)
{
	int i, flags, gitmodules_modified = 0;
	int verbose = 0, show_only = 0, force = 0, ignore_errors = 0;
	struct option builtin_mv_options[] = {
		OPT__VERBOSE(&verbose, N_("be verbose")),
		OPT__DRY_RUN(&show_only, N_("dry run")),
		OPT__FORCE(&force, N_("force move/rename even if target exists")),
		OPT_BOOL('k', NULL, &ignore_errors, N_("skip move/rename errors")),
		OPT_END(),
	};
	const char **source, **destination, **dest_path, **submodule_gitfile;
	enum update_mode { BOTH = 0, WORKING_DIRECTORY, INDEX } *modes;
	struct stat st;
	struct string_list src_for_dst = STRING_LIST_INIT_NODUP;

	gitmodules_config();
	git_config(git_default_config, NULL);

	argc = parse_options(argc, argv, prefix, builtin_mv_options,
			     builtin_mv_usage, 0);
	if (--argc < 1)
		usage_with_options(builtin_mv_usage, builtin_mv_options);

	hold_locked_index(&lock_file, LOCK_DIE_ON_ERROR);
	if (read_cache() < 0)
		die(_("index file corrupt"));

	source = internal_prefix_pathspec(prefix, argv, argc, 0);
	modes = xcalloc(argc, sizeof(enum update_mode));
	/*
	 * Keep trailing slash, needed to let
	 * "git mv file no-such-dir/" error out, except in the case
	 * "git mv directory no-such-dir/".
	 */
	flags = KEEP_TRAILING_SLASH;
	if (argc == 1 && is_directory(argv[0]) && !is_directory(argv[1]))
		flags = 0;
	dest_path = internal_prefix_pathspec(prefix, argv + argc, 1, flags);
	submodule_gitfile = xcalloc(argc, sizeof(char *));

	if (dest_path[0][0] == '\0')
		/* special case: "." was normalized to "" */
		destination = internal_prefix_pathspec(dest_path[0], argv, argc, DUP_BASENAME);
	else if (!lstat(dest_path[0], &st) &&
			S_ISDIR(st.st_mode)) {
		dest_path[0] = add_slash(dest_path[0]);
		destination = internal_prefix_pathspec(dest_path[0], argv, argc, DUP_BASENAME);
	} else {
		if (argc != 1)
			die(_("destination '%s' is not a directory"), dest_path[0]);
		destination = dest_path;
	}

	/* Checking */
	for (i = 0; i < argc; i++) {
		const char *src = source[i], *dst = destination[i];
		int length, src_is_dir;
		const char *bad = NULL;

		if (show_only)
			printf(_("Checking rename of '%s' to '%s'\n"), src, dst);

		length = strlen(src);
		if (lstat(src, &st) < 0)
			bad = _("bad source");
		else if (!strncmp(src, dst, length) &&
				(dst[length] == 0 || dst[length] == '/')) {
			bad = _("can not move directory into itself");
		} else if ((src_is_dir = S_ISDIR(st.st_mode))
				&& lstat(dst, &st) == 0)
			bad = _("cannot move directory over file");
		else if (src_is_dir) {
			int first = cache_name_pos(src, length), last;

			if (first >= 0)
				prepare_move_submodule(src, first,
						       submodule_gitfile + i);
			else if (index_range_of_same_dir(src, length,
							 &first, &last) < 1)
				bad = _("source directory is empty");
			else { /* last - first >= 1 */
				int j, dst_len, n;

				modes[i] = WORKING_DIRECTORY;
				n = argc + last - first;
				REALLOC_ARRAY(source, n);
				REALLOC_ARRAY(destination, n);
				REALLOC_ARRAY(modes, n);
				REALLOC_ARRAY(submodule_gitfile, n);

				dst = add_slash(dst);
				dst_len = strlen(dst);

				for (j = 0; j < last - first; j++) {
					const char *path = active_cache[first + j]->name;
					source[argc + j] = path;
					destination[argc + j] =
						prefix_path(dst, dst_len, path + length + 1);
					modes[argc + j] = INDEX;
					submodule_gitfile[argc + j] = NULL;
				}
				argc += last - first;
			}
		} else if (cache_name_pos(src, length) < 0)
			bad = _("not under version control");
		else if (lstat(dst, &st) == 0 &&
			 (!ignore_case || strcasecmp(src, dst))) {
			bad = _("destination exists");
			if (force) {
				/*
				 * only files can overwrite each other:
				 * check both source and destination
				 */
				if (S_ISREG(st.st_mode) || S_ISLNK(st.st_mode)) {
					if (verbose)
						warning(_("overwriting '%s'"), dst);
					bad = NULL;
				} else
					bad = _("Cannot overwrite");
			}
		} else if (string_list_has_string(&src_for_dst, dst))
			bad = _("multiple sources for the same target");
		else if (is_dir_sep(dst[strlen(dst) - 1]))
			bad = _("destination directory does not exist");
		else
			string_list_insert(&src_for_dst, dst);

		if (!bad)
			continue;
		if (!ignore_errors)
			die(_("%s, source=%s, destination=%s"),
			     bad, src, dst);
		if (--argc > 0) {
			int n = argc - i;
			memmove(source + i, source + i + 1,
				n * sizeof(char *));
			memmove(destination + i, destination + i + 1,
				n * sizeof(char *));
			memmove(modes + i, modes + i + 1,
				n * sizeof(enum update_mode));
			memmove(submodule_gitfile + i, submodule_gitfile + i + 1,
				n * sizeof(char *));
			i--;
		}
	}

	for (i = 0; i < argc; i++) {
		const char *src = source[i], *dst = destination[i];
		enum update_mode mode = modes[i];
		int pos;
		if (show_only || verbose)
			printf(_("Renaming %s to %s\n"), src, dst);
		if (show_only)
			continue;
		if (mode != INDEX && rename(src, dst) < 0) {
			if (ignore_errors)
				continue;
			die_errno(_("renaming '%s' failed"), src);
		}
		if (submodule_gitfile[i]) {
			if (submodule_gitfile[i] != SUBMODULE_WITH_GITDIR)
				connect_work_tree_and_git_dir(dst, submodule_gitfile[i]);
			if (!update_path_in_gitmodules(src, dst))
				gitmodules_modified = 1;
		}

		if (mode == WORKING_DIRECTORY)
			continue;

		pos = cache_name_pos(src, strlen(src));
		assert(pos >= 0);
		if (!show_only)
			rename_cache_entry_at(pos, dst);
	}

	if (gitmodules_modified)
		stage_updated_gitmodules();

	if (active_cache_changed &&
	    write_locked_index(&the_index, &lock_file, COMMIT_LOCK))
		die(_("Unable to write new index file"));

	return 0;
}