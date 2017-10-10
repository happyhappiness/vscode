 * If the work tree has unstaged or uncommitted changes, dies with the
 * appropriate message.
 */
int require_clean_work_tree(const char *action, const char *hint, int ignore_submodules, int gently)
{
	struct lock_file *lock_file = xcalloc(1, sizeof(*lock_file));
	int err = 0;

	hold_locked_index(lock_file, 0);
	refresh_cache(REFRESH_QUIET);
	update_index_if_able(&the_index, lock_file);
	rollback_lock_file(lock_file);

	if (has_unstaged_changes(ignore_submodules)) {
		/* TRANSLATORS: the action is e.g. "pull with rebase" */
		error(_("cannot %s: You have unstaged changes."), _(action));
		err = 1;
