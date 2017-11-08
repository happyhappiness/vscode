int refs_read_ref_full(struct ref_store *refs, const char *refname,
		       int resolve_flags, unsigned char *sha1, int *flags)
{
	if (refs_resolve_ref_unsafe(refs, refname, resolve_flags, sha1, flags))
		return 0;
	return -1;
}