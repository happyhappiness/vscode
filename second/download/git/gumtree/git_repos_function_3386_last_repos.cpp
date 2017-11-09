int read_ref_full(const char *refname, int resolve_flags, unsigned char *sha1, int *flags)
{
	return refs_read_ref_full(get_main_ref_store(), refname,
				  resolve_flags, sha1, flags);
}