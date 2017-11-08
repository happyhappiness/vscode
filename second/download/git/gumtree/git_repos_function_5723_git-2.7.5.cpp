const char *resolve_ref_unsafe(const char *refname, int resolve_flags,
			       unsigned char *sha1, int *flags)
{
	static struct strbuf sb_refname = STRBUF_INIT;
	struct strbuf sb_contents = STRBUF_INIT;
	struct strbuf sb_path = STRBUF_INIT;
	const char *ret;

	ret = resolve_ref_1(refname, resolve_flags, sha1, flags,
			    &sb_refname, &sb_path, &sb_contents);
	strbuf_release(&sb_path);
	strbuf_release(&sb_contents);
	return ret;
}