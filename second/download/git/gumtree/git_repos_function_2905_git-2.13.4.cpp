static int add_recent_loose(const struct object_id *oid,
			    const char *path, void *data)
{
	struct stat st;
	struct object *obj = lookup_object(oid->hash);

	if (obj && obj->flags & SEEN)
		return 0;

	if (stat(path, &st) < 0) {
		/*
		 * It's OK if an object went away during our iteration; this
		 * could be due to a simultaneous repack. But anything else
		 * we should abort, since we might then fail to mark objects
		 * which should not be pruned.
		 */
		if (errno == ENOENT)
			return 0;
		return error_errno("unable to stat %s", oid_to_hex(oid));
	}

	add_recent_object(oid, st.st_mtime, data);
	return 0;
}