static void update_paths(struct string_list *update)
{
	int i;

	hold_locked_index(&index_lock, 1);

	for (i = 0; i < update->nr; i++) {
		struct string_list_item *item = &update->items[i];
		if (add_file_to_cache(item->string, 0))
			exit(128);
		fprintf(stderr, "Staged '%s' using previous resolution.\n",
			item->string);
	}

	if (active_cache_changed) {
		if (write_locked_index(&the_index, &index_lock, COMMIT_LOCK))
			die("Unable to write new index file");
	} else
		rollback_lock_file(&index_lock);
}