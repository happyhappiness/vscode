char *refs_resolve_refdup(struct ref_store *refs,
			  const char *refname, int resolve_flags,
			  unsigned char *sha1, int *flags)
{
	const char *result;

	result = refs_resolve_ref_unsafe(refs, refname, resolve_flags,
					 sha1, flags);
	return xstrdup_or_null(result);
}