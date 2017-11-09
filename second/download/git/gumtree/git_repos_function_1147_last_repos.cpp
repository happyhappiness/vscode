int require_clean_work_tree(const char *action, const char *hint, int ignore_submodules, int gently)
{
	struct lock_file *lock_file = xcalloc(1, sizeof(*lock_file));
	int err = 0, fd;

	fd = hold_locked_index(lock_file, 0);
	refresh_cache(REFRESH_QUIET);
	if (0 <= fd)
		update_index_if_able(&the_index, lock_file);
	rollback_lock_file(lock_file);

	if (has_unstaged_changes(ignore_submodules)) {
		/* TRANSLATORS: the action is e.g. "pull with rebase" */
		error(_("cannot %s: You have unstaged changes."), _(action));
		err = 1;
	}

	if (has_uncommitted_changes(ignore_submodules)) {
		if (err)
			error(_("additionally, your index contains uncommitted changes."));
		else
			error(_("cannot %s: Your index contains uncommitted changes."),
			      _(action));
		err = 1;
	}

	if (err) {
		if (hint)
			error("%s", hint);
		if (!gently)
			exit(128);
	}

	return err;
}