static int rerere_forget_one_path(const char *path, struct string_list *rr)
{
	const char *filename;
	struct rerere_id *id;
	unsigned char sha1[20];
	int ret;
	struct string_list_item *item;

	/*
	 * Recreate the original conflict from the stages in the
	 * index and compute the conflict ID
	 */
	ret = handle_cache(path, sha1, NULL);
	if (ret < 1)
		return error("Could not parse conflict hunks in '%s'", path);

	/* Nuke the recorded resolution for the conflict */
	id = new_rerere_id(sha1);

	for (id->variant = 0;
	     id->variant < id->collection->status_nr;
	     id->variant++) {
		mmfile_t cur = { NULL, 0 };
		mmbuffer_t result = {NULL, 0};
		int cleanly_resolved;

		if (!has_rerere_resolution(id))
			continue;

		handle_cache(path, sha1, rerere_path(id, "thisimage"));
		if (read_mmfile(&cur, rerere_path(id, "thisimage"))) {
			free(cur.ptr);
			error("Failed to update conflicted state in '%s'", path);
			goto fail_exit;
		}
		cleanly_resolved = !try_merge(id, path, &cur, &result);
		free(result.ptr);
		free(cur.ptr);
		if (cleanly_resolved)
			break;
	}

	if (id->collection->status_nr <= id->variant) {
		error("no remembered resolution for '%s'", path);
		goto fail_exit;
	}

	filename = rerere_path(id, "postimage");
	if (unlink(filename)) {
		if (errno == ENOENT)
			error("no remembered resolution for %s", path);
		else
			error_errno("cannot unlink %s", filename);
		goto fail_exit;
	}

	/*
	 * Update the preimage so that the user can resolve the
	 * conflict in the working tree, run us again to record
	 * the postimage.
	 */
	handle_cache(path, sha1, rerere_path(id, "preimage"));
	fprintf(stderr, "Updated preimage for '%s'\n", path);

	/*
	 * And remember that we can record resolution for this
	 * conflict when the user is done.
	 */
	item = string_list_insert(rr, path);
	free_rerere_id(item);
	item->util = id;
	fprintf(stderr, "Forgot resolution for %s\n", path);
	return 0;

fail_exit:
	free(id);
	return -1;
}