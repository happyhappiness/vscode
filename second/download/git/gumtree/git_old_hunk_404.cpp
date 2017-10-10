		return 0;
	}
	return git_default_config(var, value, cb);
}

/**
 * Returns 1 if there are unstaged changes, 0 otherwise.
 */
static int has_unstaged_changes(const char *prefix)
{
	struct rev_info rev_info;
	int result;

	init_revisions(&rev_info, prefix);
	DIFF_OPT_SET(&rev_info.diffopt, IGNORE_SUBMODULES);
	DIFF_OPT_SET(&rev_info.diffopt, QUICK);
	diff_setup_done(&rev_info.diffopt);
	result = run_diff_files(&rev_info, 0);
	return diff_result_code(&rev_info.diffopt, result);
}

/**
 * Returns 1 if there are uncommitted changes, 0 otherwise.
 */
static int has_uncommitted_changes(const char *prefix)
{
	struct rev_info rev_info;
	int result;

	if (is_cache_unborn())
		return 0;

	init_revisions(&rev_info, prefix);
	DIFF_OPT_SET(&rev_info.diffopt, IGNORE_SUBMODULES);
	DIFF_OPT_SET(&rev_info.diffopt, QUICK);
	add_head_to_pending(&rev_info);
	diff_setup_done(&rev_info.diffopt);
	result = run_diff_index(&rev_info, 1);
	return diff_result_code(&rev_info.diffopt, result);
}

/**
 * If the work tree has unstaged or uncommitted changes, dies with the
 * appropriate message.
 */
static void die_on_unclean_work_tree(const char *prefix)
{
	struct lock_file *lock_file = xcalloc(1, sizeof(*lock_file));
	int do_die = 0;

	hold_locked_index(lock_file, 0);
	refresh_cache(REFRESH_QUIET);
	update_index_if_able(&the_index, lock_file);
	rollback_lock_file(lock_file);

	if (has_unstaged_changes(prefix)) {
		error(_("Cannot pull with rebase: You have unstaged changes."));
		do_die = 1;
	}

	if (has_uncommitted_changes(prefix)) {
		if (do_die)
			error(_("Additionally, your index contains uncommitted changes."));
		else
			error(_("Cannot pull with rebase: Your index contains uncommitted changes."));
		do_die = 1;
	}

	if (do_die)
		exit(1);
}

/**
 * Appends merge candidates from FETCH_HEAD that are not marked not-for-merge
 * into merge_heads.
 */
static void get_merge_heads(struct sha1_array *merge_heads)
{
	const char *filename = git_path("FETCH_HEAD");
