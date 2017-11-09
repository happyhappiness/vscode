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

		/* Ensure that the directory exists. */
		mkdir_in_gitdir(rerere_path(id, NULL));
	}

	for (i = 0; i < rr->nr; i++)
		do_rerere_one_path(&rr->items[i], &update);

	if (update.nr)
		update_paths(&update);

	return write_rr(rr, fd);
}