static char *resolve_symref(const char *src, const char *prefix)
{
	unsigned char sha1[20];
	int flag;
	const char *dst, *cp;

	dst = resolve_ref_unsafe(src, sha1, 0, &flag);
	if (!(dst && (flag & REF_ISSYMREF)))
		return NULL;
	if (prefix && (cp = skip_prefix(dst, prefix)))
		dst = cp;
	return xstrdup(dst);
}