static void refresh_index_quietly(void)
{
	struct lock_file *lock_file;
	int fd;

	lock_file = xcalloc(1, sizeof(struct lock_file));
	fd = hold_locked_index(lock_file, 0);
	if (fd < 0)
		return;
	discard_cache();
	read_cache();
	refresh_cache(REFRESH_QUIET|REFRESH_UNMERGED);
	update_index_if_able(&the_index, lock_file);
}