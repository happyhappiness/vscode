char *resolve_refdup(const char *ref, unsigned char *sha1, int reading, int *flag)
{
	const char *ret = resolve_ref_unsafe(ref, sha1, reading, flag);
	return ret ? xstrdup(ret) : NULL;
}