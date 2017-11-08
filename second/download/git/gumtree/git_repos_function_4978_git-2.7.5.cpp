static int show_ref_cb(const char *path_full, const struct object_id *oid,
		       int flag, void *unused)
{
	const char *path = strip_namespace(path_full);

	if (ref_is_hidden(path, path_full))
		return 0;

	/*
	 * Advertise refs outside our current namespace as ".have"
	 * refs, so that the client can use them to minimize data
	 * transfer but will otherwise ignore them. This happens to
	 * cover ".have" that are thrown in by add_one_alternate_ref()
	 * to mark histories that are complete in our alternates as
	 * well.
	 */
	if (!path)
		path = ".have";
	show_ref(path, oid->hash);
	return 0;
}