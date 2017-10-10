
	return ret;
}

static struct lock_file index_lock;

static void update_paths(struct string_list *update)
{
	int i;

	hold_locked_index(&index_lock, 1);

	for (i = 0; i < update->nr; i++) {
		struct string_list_item *item = &update->items[i];
		if (add_file_to_cache(item->string, 0))
			exit(128);
	}

	if (active_cache_changed) {
		if (write_locked_index(&the_index, &index_lock, COMMIT_LOCK))
			die("Unable to write new index file");
	} else
		rollback_lock_file(&index_lock);
}

static int do_plain_rerere(struct string_list *rr, int fd)
{
	struct string_list conflict = STRING_LIST_INIT_DUP;
	struct string_list update = STRING_LIST_INIT_DUP;
