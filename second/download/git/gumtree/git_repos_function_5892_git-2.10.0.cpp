int resolve_gitlink_ref(const char *path, const char *refname, unsigned char *sha1)
{
	int len = strlen(path), retval;
	struct strbuf submodule = STRBUF_INIT;
	struct ref_cache *refs;

	while (len && path[len-1] == '/')
		len--;
	if (!len)
		return -1;

	strbuf_add(&submodule, path, len);
	refs = get_ref_cache(submodule.buf);
	if (!refs) {
		strbuf_release(&submodule);
		return -1;
	}
	strbuf_release(&submodule);

	retval = resolve_gitlink_ref_recursive(refs, refname, sha1, 0);
	return retval;
}