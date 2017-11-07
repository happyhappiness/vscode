static int update_paths(struct string_list *update)
{
	int i;
	int fd = hold_locked_index(&index_lock, 0);
	int status = 0;

	if (fd < 0)
		return -1;

	for (i = 0; i < update->nr; i++) {
		struct string_list_item *item = &update->items[i];
		if (add_file_to_cache(item->string, ADD_CACHE_IGNORE_ERRORS))
			status = -1;
	}

	if (!status && active_cache_changed) {
		if (write_cache(fd, active_cache, active_nr) ||
		    commit_locked_index(&index_lock))
			die("Unable to write new index file");
	} else if (fd >= 0)
		rollback_lock_file(&index_lock);
	return status;
}