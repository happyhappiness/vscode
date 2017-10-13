int cmd_rm(int argc, const char **argv, const char *prefix)
{
	int i;
	struct pathspec pathspec;
	char *seen;

	gitmodules_config();
	git_config(git_default_config, NULL);

	argc = parse_options(argc, argv, prefix, builtin_rm_options,
			     builtin_rm_usage, 0);
	if (!argc)
		usage_with_options(builtin_rm_usage, builtin_rm_options);

	if (!index_only)
		setup_work_tree();

	hold_locked_index(&lock_file, LOCK_DIE_ON_ERROR);

	if (read_cache() < 0)
		die(_("index file corrupt"));

	parse_pathspec(&pathspec, 0,
		       PATHSPEC_PREFER_CWD |
		       PATHSPEC_STRIP_SUBMODULE_SLASH_CHEAP,
		       prefix, argv);
	refresh_index(&the_index, REFRESH_QUIET, &pathspec, NULL, NULL);

	seen = xcalloc(pathspec.nr, 1);

	for (i = 0; i < active_nr; i++) {
		const struct cache_entry *ce = active_cache[i];
		if (!ce_path_match(ce, &pathspec, seen))
			continue;
		ALLOC_GROW(list.entry, list.nr + 1, list.alloc);
		list.entry[list.nr].name = xstrdup(ce->name);
		list.entry[list.nr].is_submodule = S_ISGITLINK(ce->ce_mode);
		if (list.entry[list.nr++].is_submodule &&
		    !is_staging_gitmodules_ok())
			die (_("Please stage your changes to .gitmodules or stash them to proceed"));
	}

	if (pathspec.nr) {
		const char *original;
		int seen_any = 0;
		for (i = 0; i < pathspec.nr; i++) {
			original = pathspec.items[i].original;
			if (!seen[i]) {
				if (!ignore_unmatch) {
					die(_("pathspec '%s' did not match any files"),
					    original);
				}
			}
			else {
				seen_any = 1;
			}
			if (!recursive && seen[i] == MATCHED_RECURSIVELY)
				die(_("not removing '%s' recursively without -r"),
				    *original ? original : ".");
		}

		if (!seen_any)
			exit(0);
	}

	if (!index_only)
		submodules_absorb_gitdir_if_needed(prefix);

	/*
	 * If not forced, the file, the index and the HEAD (if exists)
	 * must match; but the file can already been removed, since
	 * this sequence is a natural "novice" way:
	 *
	 *	rm F; git rm F
	 *
	 * Further, if HEAD commit exists, "diff-index --cached" must
	 * report no changes unless forced.
	 */
	if (!force) {
		struct object_id oid;
		if (get_oid("HEAD", &oid))
			oidclr(&oid);
		if (check_local_mod(&oid, index_only))
			exit(1);
	}

	/*
	 * First remove the names from the index: we won't commit
	 * the index unless all of them succeed.
	 */
	for (i = 0; i < list.nr; i++) {
		const char *path = list.entry[i].name;
		if (!quiet)
			printf("rm '%s'\n", path);

		if (remove_file_from_cache(path))
			die(_("git rm: unable to remove %s"), path);
	}

	if (show_only)
		return 0;

	/*
	 * Then, unless we used "--cached", remove the filenames from
	 * the workspace. If we fail to remove the first one, we
	 * abort the "git rm" (but once we've successfully removed
	 * any file at all, we'll go ahead and commit to it all:
	 * by then we've already committed ourselves and can't fail
	 * in the middle)
	 */
	if (!index_only) {
		int removed = 0, gitmodules_modified = 0;
		struct strbuf buf = STRBUF_INIT;
		for (i = 0; i < list.nr; i++) {
			const char *path = list.entry[i].name;
			if (list.entry[i].is_submodule) {
				strbuf_reset(&buf);
				strbuf_addstr(&buf, path);
				if (remove_dir_recursively(&buf, 0))
					die(_("could not remove '%s'"), path);

				removed = 1;
				if (!remove_path_from_gitmodules(path))
					gitmodules_modified = 1;
				continue;
			}
			if (!remove_path(path)) {
				removed = 1;
				continue;
			}
			if (!removed)
				die_errno("git rm: '%s'", path);
		}
		strbuf_release(&buf);
		if (gitmodules_modified)
			stage_updated_gitmodules();
	}

	if (active_cache_changed) {
		if (write_locked_index(&the_index, &lock_file, COMMIT_LOCK))
			die(_("Unable to write new index file"));
	}

	return 0;
}