const char *resolve_ref_unsafe(const char *refname, int resolve_flags,
			       unsigned char *sha1, int *flags)
{
	return refs_resolve_ref_unsafe(get_main_ref_store(), refname,
				       resolve_flags, sha1, flags);
}