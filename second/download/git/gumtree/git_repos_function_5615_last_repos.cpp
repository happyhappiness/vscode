static int show_ref_cb(const char *path_full, const struct object_id *oid,
		       int flag, void *data)
{
	struct oidset *seen = data;
	const char *path = strip_namespace(path_full);

	if (ref_is_hidden(path, path_full))
		return 0;

	/*
	 * Advertise refs outside our current namespace as ".have"
	 * refs, so that the client can use them to minimize data
	 * transfer but will otherwise ignore them.
	 */
	if (!path) {
		if (oidset_insert(seen, oid))
			return 0;
		path = ".have";
	} else {
		oidset_insert(seen, oid);
	}
	show_ref(path, oid);
	return 0;
}