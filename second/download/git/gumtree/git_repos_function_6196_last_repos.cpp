static void hash_stdin_paths(const char *type, int no_filters, unsigned flags,
			     int literally)
{
	struct strbuf buf = STRBUF_INIT;
	struct strbuf unquoted = STRBUF_INIT;

	while (strbuf_getline(&buf, stdin) != EOF) {
		if (buf.buf[0] == '"') {
			strbuf_reset(&unquoted);
			if (unquote_c_style(&unquoted, buf.buf, NULL))
				die("line is badly quoted");
			strbuf_swap(&buf, &unquoted);
		}
		hash_object(buf.buf, type, no_filters ? NULL : buf.buf, flags,
			    literally);
	}
	strbuf_release(&buf);
	strbuf_release(&unquoted);
}