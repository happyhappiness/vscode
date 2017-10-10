 * Refresh and write index.
 */
static void refresh_and_write_cache(void)
{
	struct lock_file *lock_file = xcalloc(1, sizeof(struct lock_file));

	hold_locked_index(lock_file, LOCK_DIE_ON_ERROR);
	refresh_cache(REFRESH_QUIET);
	if (write_locked_index(&the_index, lock_file, COMMIT_LOCK))
		die(_("unable to write index file"));
}

/**
