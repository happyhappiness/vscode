static int process_directory(const char *path, int len, struct stat *st)
{
	struct object_id oid;
	int pos = cache_name_pos(path, len);

	/* Exact match: file or existing gitlink */
	if (pos >= 0) {
		const struct cache_entry *ce = active_cache[pos];
		if (S_ISGITLINK(ce->ce_mode)) {

			/* Do nothing to the index if there is no HEAD! */
			if (resolve_gitlink_ref(path, "HEAD", oid.hash) < 0)
				return 0;

			return add_one_path(ce, path, len, st);
		}
		/* Should this be an unconditional error? */
		return remove_one_path(path);
	}

	/* Inexact match: is there perhaps a subdirectory match? */
	pos = -pos-1;
	while (pos < active_nr) {
		const struct cache_entry *ce = active_cache[pos++];

		if (strncmp(ce->name, path, len))
			break;
		if (ce->name[len] > '/')
			break;
		if (ce->name[len] < '/')
			continue;

		/* Subdirectory match - error out */
		return error("%s: is a directory - add individual files instead", path);
	}

	/* No match - should we add it as a gitlink? */
	if (!resolve_gitlink_ref(path, "HEAD", oid.hash))
		return add_one_path(NULL, path, len, st);

	/* Error out. */
	return error("%s: is a directory - add files inside instead", path);
}