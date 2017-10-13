tatic const char *prepare_index(int argc, const char **argv, const char *prefix,
				 const struct commit *current_head, int is_status)
{
	struct string_list partial;
	struct pathspec pathspec;
	int refresh_flags = REFRESH_QUIET;

	if (is_status)
		refresh_flags |= REFRESH_UNMERGED;
	parse_pathspec(&pathspec, 0,
		       PATHSPEC_PREFER_FULL,
		       prefix, argv);

	if (read_cache_preload(&pathspec) < 0)
		die(_("index file corrupt"));

	if (interactive) {
		char *old_index_env = NULL;
		hold_locked_index(&index_lock, 1);

		refresh_cache_or_die(refresh_flags);

		if (write_locked_index(&the_index, &index_lock, CLOSE_LOCK))
			die(_("unable to create temporary index"));

		old_index_env = getenv(INDEX_ENVIRONMENT);
		setenv(INDEX_ENVIRONMENT, index_lock.filename.buf, 1);

		if (interactive_add(argc, argv, prefix, patch_interactive) != 0)
			die(_("interactive add failed"));

		if (old_index_env && *old_index_env)
			setenv(INDEX_ENVIRONMENT, old_index_env, 1);
		else
			unsetenv(INDEX_ENVIRONMENT);

		discard_cache();
		read_cache_from(index_lock.filename.buf);
		if (update_main_cache_tree(WRITE_TREE_SILENT) == 0) {
			if (reopen_lock_file(&index_lock) < 0)
				die(_("unable to write index file"));
			if (write_locked_index(&the_index, &index_lock, CLOSE_LOCK))
				die(_("unable to update temporary index"));
		} else
			warning(_("Failed to update main cache tree"));

		commit_style = COMMIT_NORMAL;
		return index_lock.filename.buf;
	}

	/*
	 * Non partial, non as-is commit.
	 *
	 * (1) get the real index;
	 * (2) update the_index as necessary;
	 * (3) write the_index out to the real index (still locked);
	 * (4) return the name of the locked index file.
	 *
	 * The caller should run hooks on the locked real index, and
	 * (A) if all goes well, commit the real index;
	 * (B) on failure, rollback the real index.
	 */
	if (all || (also && pathspec.nr)) {
		hold_locked_index(&index_lock, 1);
		add_files_to_cache(also ? prefix : NULL, &pathspec, 0);
		refresh_cache_or_die(refresh_flags);
		update_main_cache_tree(WRITE_TREE_SILENT);
		if (write_locked_index(&the_index, &index_lock, CLOSE_LOCK))
			die(_("unable to write new_index file"));
		commit_style = COMMIT_NORMAL;
		return index_lock.filename.buf;
	}

	/*
	 * As-is commit.
	 *
	 * (1) return the name of the real index file.
	 *
	 * The caller should run hooks on the real index,
	 * and create commit from the_index.
	 * We still need to refresh the index here.
	 */
	if (!only && !pathspec.nr) {
		hold_locked_index(&index_lock, 1);
		refresh_cache_or_die(refresh_flags);
		if (active_cache_changed
		    || !cache_tree_fully_valid(active_cache_tree)) {
			update_main_cache_tree(WRITE_TREE_SILENT);
			active_cache_changed = 1;
		}
		if (active_cache_changed) {
			if (write_locked_index(&the_index, &index_lock,
					       COMMIT_LOCK))
				die(_("unable to write new_index file"));
		} else {
			rollback_lock_file(&index_lock);
		}
		commit_style = COMMIT_AS_IS;
		return get_index_file();
	}

	/*
	 * A partial commit.
	 *
	 * (0) find the set of affected paths;
	 * (1) get lock on the real index file;
	 * (2) update the_index with the given paths;
	 * (3) write the_index out to the real index (still locked);
	 * (4) get lock on the false index file;
	 * (5) reset the_index from HEAD;
	 * (6) update the_index the same way as (2);
	 * (7) write the_index out to the false index file;
	 * (8) return the name of the false index file (still locked);
	 *
	 * The caller should run hooks on the locked false index, and
	 * create commit from it.  Then
	 * (A) if all goes well, commit the real index;
	 * (B) on failure, rollback the real index;
	 * In either case, rollback the false index.
	 */
	commit_style = COMMIT_PARTIAL;

	if (whence != FROM_COMMIT) {
		if (whence == FROM_MERGE)
			die(_("cannot do a partial commit during a merge."));
		else if (whence == FROM_CHERRY_PICK)
			die(_("cannot do a partial commit during a cherry-pick."));
	}

	string_list_init(&partial, 1);
	if (list_paths(&partial, !current_head ? NULL : "HEAD", prefix, &pathspec))
		exit(1);

	discard_cache();
	if (read_cache() < 0)
		die(_("cannot read the index"));

	hold_locked_index(&index_lock, 1);
	add_remove_files(&partial);
	refresh_cache(REFRESH_QUIET);
	update_main_cache_tree(WRITE_TREE_SILENT);
	if (write_locked_index(&the_index, &index_lock, CLOSE_LOCK))
		die(_("unable to write new_index file"));

	hold_lock_file_for_update(&false_lock,
				  git_path("next-index-%"PRIuMAX,
					   (uintmax_t) getpid()),
				  LOCK_DIE_ON_ERROR);

	create_base_index(current_head);
	add_remove_files(&partial);
	refresh_cache(REFRESH_QUIET);

	if (write_locked_index(&the_index, &false_lock, CLOSE_LOCK))
		die(_("unable to write temporary index file"));

	discard_cache();
	read_cache_from(false_lock.filename.buf);

	return false_lock.filename.buf;
}