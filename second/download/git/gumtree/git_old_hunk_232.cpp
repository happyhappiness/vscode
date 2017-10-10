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

