char *resolve_refdup(const char *ref, int resolve_flags, unsigned char *sha1, int *flags)
{
	return xstrdup_or_null(resolve_ref_unsafe(ref, resolve_flags, sha1, flags));
}