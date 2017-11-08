static int show_reference(const char *refname, const unsigned char *sha1, int flag, void *cb_data)
{
	if (ref_excluded(ref_excludes, refname))
		return 0;
	show_rev(NORMAL, sha1, refname);
	return 0;
}