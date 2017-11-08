int read_ref_full(const char *refname, unsigned char *sha1, int reading, int *flags)
{
	if (resolve_ref_unsafe(refname, sha1, reading, flags))
		return 0;
	return -1;
}