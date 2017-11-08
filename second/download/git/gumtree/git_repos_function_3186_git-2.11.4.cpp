const char *resolve_ref_unsafe(const char *refname, int resolve_flags,
			       unsigned char *sha1, int *flags)
{
	return resolve_ref_recursively(get_ref_store(NULL), refname,
				       resolve_flags, sha1, flags);
}