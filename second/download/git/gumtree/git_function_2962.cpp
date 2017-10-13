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
	filename = rerere_path(id, "postimage");
	if (unlink(filename))
		return (errno == ENOENT
			? error("no remembered resolution for %s", path)
			: error("cannot unlink %s: %s", filename, strerror(errno)));

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
}