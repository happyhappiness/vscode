static char *resolve_symref(const char *src, const char *prefix)
{
	unsigned char sha1[20];
	int flag;
	const char *dst;

	dst = resolve_ref_unsafe(src, 0, sha1, &flag);
	if (!(dst && (flag & REF_ISSYMREF)))
		return NULL;
	if (prefix)
		skip_prefix(dst, prefix, &dst);
	return xstrdup(dst);
}