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
