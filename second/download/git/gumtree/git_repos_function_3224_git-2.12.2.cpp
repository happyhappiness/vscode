int resolve_gitlink_ref(const char *submodule, const char *refname,
			unsigned char *sha1)
{
	size_t len = strlen(submodule);
	struct ref_store *refs;
	int flags;

	while (len && submodule[len - 1] == '/')
		len--;

	if (!len)
		return -1;

	if (submodule[len]) {
		/* We need to strip off one or more trailing slashes */
		char *stripped = xmemdupz(submodule, len);

		refs = get_ref_store(stripped);
		free(stripped);
	} else {
		refs = get_ref_store(submodule);
	}

	if (!refs)
		return -1;

	if (!resolve_ref_recursively(refs, refname, 0, sha1, &flags) ||
	    is_null_sha1(sha1))
		return -1;
	return 0;
}