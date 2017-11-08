const char *resolve_ref_unsafe(const char *refname, int resolve_flags,
			       unsigned char *sha1, int *flags)
{
	struct strbuf sb_path = STRBUF_INIT;
	const char *ret = resolve_ref_unsafe_1(refname, resolve_flags,
					       sha1, flags, &sb_path);
	strbuf_release(&sb_path);
	return ret;
}