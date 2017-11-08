static int append_remote_ref(const char *refname, const unsigned char *sha1, int flag, void *cb_data)
{
	unsigned char tmp[20];
	int ofs = 13;
	if (!starts_with(refname, "refs/remotes/"))
		return 0;
	/* If both heads/foo and tags/foo exists, get_sha1 would
	 * get confused.
	 */
	if (get_sha1(refname + ofs, tmp) || hashcmp(tmp, sha1))
		ofs = 5;
	return append_ref(refname + ofs, sha1, 0);
}