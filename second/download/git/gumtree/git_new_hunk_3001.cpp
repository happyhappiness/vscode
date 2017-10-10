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

/*
 * The path indicated by rr_item may still have conflict for which we
 * have a recorded resolution, in which case replay it and optionally
 * update it.  Or it may have been resolved by the user and we may
 * only have the preimage for that conflict, in which case the result
 * needs to be recorded as a resolution in a postimage file.
 */
static void do_rerere_one_path(struct string_list_item *rr_item,
			       struct string_list *update)
{
	const char *path = rr_item->string;
	const struct rerere_id *id = rr_item->util;

	/* Is there a recorded resolution we could attempt to apply? */
	if (has_rerere_resolution(id)) {
		if (merge(id, path))
			return; /* failed to replay */

		if (rerere_autoupdate)
			string_list_insert(update, path);
		else
			fprintf(stderr,
				"Resolved '%s' using previous resolution.\n",
				path);
	} else if (!handle_file(path, NULL, NULL)) {
		/* The user has resolved it. */
		copy_file(rerere_path(id, "postimage"), path, 0666);
		fprintf(stderr, "Recorded resolution for '%s'.\n", path);
	} else {
		return;
	}
	free_rerere_id(rr_item);
	rr_item->util = NULL;
}

static int do_plain_rerere(struct string_list *rr, int fd)
{
	struct string_list conflict = STRING_LIST_INIT_DUP;
	struct string_list update = STRING_LIST_INIT_DUP;
	int i;

	find_conflict(&conflict);

	/*
	 * MERGE_RR records paths with conflicts immediately after
	 * merge failed.  Some of the conflicted paths might have been
	 * hand resolved in the working tree since then, but the
	 * initial run would catch all and register their preimages.
	 */
	for (i = 0; i < conflict.nr; i++) {
		struct rerere_id *id;
		unsigned char sha1[20];
		const char *path = conflict.items[i].string;
		int ret;

		if (string_list_has_string(rr, path))
			continue;

		/*
		 * Ask handle_file() to scan and assign a
		 * conflict ID.  No need to write anything out
		 * yet.
		 */
		ret = handle_file(path, sha1, NULL);
		if (ret < 1)
			continue;

		id = new_rerere_id(sha1);
		string_list_insert(rr, path)->util = id;

		/*
		 * If the directory does not exist, create
		 * it.  mkdir_in_gitdir() will fail with
		 * EEXIST if there already is one.
		 *
		 * NEEDSWORK: make sure "gc" does not remove
		 * preimage without removing the directory.
		 */
		if (mkdir_in_gitdir(rerere_path(id, NULL)))
			continue;

		/*
		 * We are the first to encounter this
		 * conflict.  Ask handle_file() to write the
		 * normalized contents to the "preimage" file.
		 */
		handle_file(path, NULL, rerere_path(id, "preimage"));
		fprintf(stderr, "Recorded preimage for '%s'\n", path);
	}

	for (i = 0; i < rr->nr; i++)
		do_rerere_one_path(&rr->items[i], &update);

	if (update.nr)
		update_paths(&update);

	return write_rr(rr, fd);
}

