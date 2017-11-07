static int prune_object(const unsigned char *sha1, const char *fullpath,
			void *data)
{
	struct stat st;

	/*
	 * Do we know about this object?
	 * It must have been reachable
	 */
	if (lookup_object(sha1))
		return 0;

	if (lstat(fullpath, &st)) {
		/* report errors, but do not stop pruning */
		error("Could not stat '%s'", fullpath);
		return 0;
	}
	if (st.st_mtime > expire)
		return 0;
	if (show_only || verbose) {
		enum object_type type = sha1_object_info(sha1, NULL);
		printf("%s %s\n", sha1_to_hex(sha1),
		       (type > 0) ? typename(type) : "unknown");
	}
	if (!show_only)
		unlink_or_warn(fullpath);
	return 0;
}