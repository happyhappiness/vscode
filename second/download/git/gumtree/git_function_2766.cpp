static int write_one_ref(const char *name, const struct object_id *oid,
			 int flags, void *data)
{
	struct strbuf *buf = data;
	int len = buf->len;

	/* when called via for_each_ref(), flags is non-zero */
	if (flags && !starts_with(name, "refs/heads/") &&
			!starts_with(name, "refs/tags/"))
		return 0;

	strbuf_addstr(buf, name);
	if (safe_create_leading_directories(buf->buf) ||
	    write_file_gently(buf->buf, "%s", oid_to_hex(oid)))
		return error("problems writing temporary file %s: %s",
			     buf->buf, strerror(errno));
	strbuf_setlen(buf, len);
	return 0;
}