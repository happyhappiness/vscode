char *resolve_refdup(const char *ref, int resolve_flags, unsigned char *sha1, int *flags)
{
	const char *ret = resolve_ref_unsafe(ref, resolve_flags, sha1, flags);
	return ret ? xstrdup(ret) : NULL;
}