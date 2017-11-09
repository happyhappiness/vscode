char *resolve_refdup(const char *refname, int resolve_flags,
		     unsigned char *sha1, int *flags)
{
	return refs_resolve_refdup(get_main_ref_store(),
				   refname, resolve_flags,
				   sha1, flags);
}