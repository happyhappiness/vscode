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