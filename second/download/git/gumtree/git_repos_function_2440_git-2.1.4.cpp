int read_ref(const char *refname, unsigned char *sha1)
{
	return read_ref_full(refname, sha1, 1, NULL);
}