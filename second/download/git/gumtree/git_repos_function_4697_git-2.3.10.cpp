static int show_ref_cb(const char *path, const unsigned char *sha1, int flag, void *unused)
{
	path = strip_namespace(path);
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
	show_ref(path, sha1);
	return 0;
}