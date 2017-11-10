static int template_untouched(struct strbuf *sb)
{
	struct strbuf tmpl = STRBUF_INIT;
	const char *start;

	if (cleanup_mode == CLEANUP_NONE && sb->len)
		return 0;

	if (!template_file || strbuf_read_file(&tmpl, template_file, 0) <= 0)
		return 0;

	strbuf_stripspace(&tmpl, cleanup_mode == CLEANUP_ALL);
	if (!skip_prefix(sb->buf, tmpl.buf, &start))
		start = sb->buf;
	strbuf_release(&tmpl);
	return rest_is_empty(sb, start - sb->buf);
}