static char *resolve_symref(const char *src, const char *prefix)
{
	unsigned char sha1[20];
	int flag;
	const char *dst;

	dst = resolve_ref_unsafe(src, sha1, 0, &flag);
	if (!(dst && (flag & REF_ISSYMREF)))
		return NULL;
	if (prefix)
		skip_prefix(dst, prefix, &dst);
	return xstrdup(dst);
}