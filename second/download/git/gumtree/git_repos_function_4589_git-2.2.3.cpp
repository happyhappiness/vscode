static int append_tag_ref(const char *refname, const unsigned char *sha1, int flag, void *cb_data)
{
	if (!starts_with(refname, "refs/tags/"))
		return 0;
	return append_ref(refname + 5, sha1, 0);
}