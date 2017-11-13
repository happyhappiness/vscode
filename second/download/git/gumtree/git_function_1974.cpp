static int write_one_ref(const char *name, const unsigned char *sha1,
		int flags, void *data)
{
	struct strbuf *buf = data;
	int len = buf->len;
	FILE *f;

	/* when called via for_each_ref(), flags is non-zero */
	if (flags && !starts_with(name, "refs/heads/") &&
			!starts_with(name, "refs/tags/"))
		return 0;

	strbuf_addstr(buf, name);
	if (safe_create_leading_directories(buf->buf) ||
			!(f = fopen(buf->buf, "w")) ||
			fprintf(f, "%s\n", sha1_to_hex(sha1)) < 0 ||
			fclose(f))
		return error("problems writing temporary file %s", buf->buf);
	strbuf_setlen(buf, len);
	return 0;
}