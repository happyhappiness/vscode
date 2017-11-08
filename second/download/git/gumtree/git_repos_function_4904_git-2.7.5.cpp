static int append_remote_ref(const char *refname, const struct object_id *oid,
			     int flag, void *cb_data)
{
	struct object_id tmp;
	int ofs = 13;
	if (!starts_with(refname, "refs/remotes/"))
		return 0;
	/* If both heads/foo and tags/foo exists, get_sha1 would
	 * get confused.
	 */
	if (get_sha1(refname + ofs, tmp.hash) || oidcmp(&tmp, oid))
		ofs = 5;
	return append_ref(refname + ofs, oid, 0);
}